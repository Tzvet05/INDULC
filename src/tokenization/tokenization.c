#include <string.h>
#include <ctype.h>
#include "indulc.h"
#include "file.h"
#include "error.h"
#include "token.h"

static bool	get_next_line(t_file* file, char** line_ptr)
{
	char*	line = NULL;
	size_t	null = 0;
	ssize_t	n_read = getline(&line, &null, file->stream);
	if (n_read == -1 && ferror(file->stream) == 1)
	{
		free(line);
		fprintf(stderr, "%s: %s: %s: \"%s\"\n",
			EXECUTABLE_NAME, FUNC_GETLINE, ERROR_READ_FILE, file->name);
		return (1);
	}
	else if (n_read == -1 && feof(file->stream) == 1)
	{
		free(line);
		*line_ptr = NULL;
	}
	else
		*line_ptr = line;
	return (0);
}

static t_token*	alloc_token(size_t len_str)
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

static t_token*	tokenize(char* line, size_t len, size_t lin, size_t col)
{
	t_token*	token = alloc_token(len);
	if (token == NULL)
		return (NULL);
	token->str[len] = '\0';
	strncpy(token->str, line, len);
	token->lin = lin;
	token->col = col;
	return (token);
}

static size_t	len_token(char* token)
{
	if (token[0] == ':')
		return (1);
	size_t	i = 0;
	while (token[i] != '\0' && isspace(token[i]) == 0
		&& token[i] != ';' && token[i] != ':' && token[i] != ',')
		i++;
	return (i);
}

static size_t	len_until_next_token(char* line)
{
	size_t	i = 0;
	while (line[i] != '\0' && (isspace(line[i]) != 0 || line[i] == ','))
		i++;
	return (i);
}

static bool	tokenize_words(t_data* data, char* line, size_t lin, size_t col)
{
	size_t		i = 0;
	while (line[i] != '\0' && line[i] != ';')
	{
		size_t	len = len_token(&line[i]);
		t_token*	token = tokenize(&line[i], len, lin, col + i);
		if (token == NULL
			|| lst_new_back((t_lst **)&(lst_last(data->tokens)->content), token) == 1)
		{
			free(token);
			fprintf(stderr, "%s: %s: %s\n",
				EXECUTABLE_NAME, FUNC_MALLOC, ERROR_FAILED_ALLOC);
			return (1);
		}
		i += len;
		i += len_until_next_token(&line[i]);
	}
	return (0);
}

static bool	tokenize_line(t_data* data, char* line, size_t lin)
{
	size_t	i = 0;
	while (line[i] != '\0' && (isspace(line[i]) != 0 || line[i] == ','))
		i++;
	if (line[i] == '\0' || line[i] == ';')
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

bool	tokenization(t_data* data)
{
	char*	line = NULL;
	size_t	lin = 1;
	while (1)
	{
		free(line);
		if (get_next_line(&data->files[INFILE_PROGRAM], &line) == 1)
			return (1);
		if (line == NULL)
			return (0);
		if (tokenize_line(data, line, lin) == 1)
		{
			free(line);
			return (1);
		}
		lin++;
	}
	return (0);
}
