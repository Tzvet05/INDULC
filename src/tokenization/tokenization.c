#include <string.h>
#include <ctype.h>
#include "indulc.h"
#include "file.h"
#include "error.h"
#include "token.h"

static t_token*	allocate_token(size_t len_str)
{
	t_token*	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->str = malloc((len_str + 1) * sizeof(char));
	if (token->str == NULL)
	{
		free(token);
		return (NULL);
	}
	return (token);
}

static t_token*	tokenize_word(char* line, size_t len, size_t lin, size_t col)
{
	t_token*	token = allocate_token(len);
	if (token == NULL)
		return (NULL);
	token->str[len] = '\0';
	strncpy(token->str, line, len);
	token->lin = lin;
	token->col = col;
	return (token);
}

static size_t	get_len_token(char* token)
{
	if (strncmp(token, LABEL_KEYWORD, strlen(LABEL_KEYWORD)) == 0)
		return (strlen(LABEL_KEYWORD));
	size_t	i = 0;
	while (token[i] != '\0' && isspace(token[i]) == 0 && token[i] != ','
		&& strncmp(&token[i], COMMENT_KEYWORD, strlen(COMMENT_KEYWORD)) != 0
		&& strncmp(&token[i], LABEL_KEYWORD, strlen(LABEL_KEYWORD)) != 0)
		i++;
	return (i);
}

static size_t	get_len_until_token(char* line)
{
	size_t	i = 0;
	while (line[i] != '\0' && (isspace(line[i]) != 0 || line[i] == ','))
		i++;
	return (i);
}

static bool	tokenize_words(t_data* data, char* line, size_t lin, size_t col)
{
	size_t		i = 0;
	while (line[i] != '\0'
		&& strncmp(&line[i], COMMENT_KEYWORD, strlen(COMMENT_KEYWORD)) != 0)
	{
		size_t	len = get_len_token(&line[i]);
		t_token*	token = tokenize_word(&line[i], len, lin, col + i);
		if (token == NULL
			|| lst_new_back((t_lst **)&(lst_last(data->tokens)->content), token) == 1)
		{
			free(token);
			fprintf(stderr, "%s: %s: %s\n",
				EXECUTABLE_NAME, FUNC_MALLOC, ERROR_FAILED_ALLOC);
			return (1);
		}
		i += len;
		i += get_len_until_token(&line[i]);
	}
	return (0);
}

static bool	tokenize_line(t_data* data, char* line, size_t lin)
{
	size_t	i = 0;
	while (line[i] != '\0' && (isspace(line[i]) != 0 || line[i] == ','))
		i++;
	if (line[i] == '\0' || strncmp(&line[i], COMMENT_KEYWORD, strlen(COMMENT_KEYWORD)) == 0)
		return (0);
	if (lst_new_back(&data->tokens, NULL) == 1)
	{
		fprintf(stderr, "%s: %s: %s\n",
			EXECUTABLE_NAME, FUNC_MALLOC, ERROR_FAILED_ALLOC);
		return (1);
	}
	if (tokenize_words(data, &line[i], lin, i + 1) == 1)
		return (1);
	return (0);
}

bool	tokenize(t_data* data)
{
	char*	line = NULL;
	size_t	lin = 1;
	while (1)
	{
		free(line);
		if (get_next_line(&data->files[INFILE_PROGRAM], &line) == 1)
		{
			fprintf(stderr, "%s: %s: %s: \"%s\"\n",
				EXECUTABLE_NAME, FUNC_GETLINE, ERROR_READ_FILE,
				data->files[INFILE_PROGRAM].name);
			return (1);
		}
		if (line == NULL)
			return (0);
		if (tokenize_line(data, line, lin) == 1)
		{
			free(line);
			return (1);
		}
		lin++;
	}
}
