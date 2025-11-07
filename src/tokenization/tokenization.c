#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "lst.h"
#include "data.h"
#include "tokenization.h"
#include "files.h"
#include "syntax.h"
#include "error.h"

static t_token	*tokenize_word(char *line, size_t len, size_t lin, size_t col)
{
	t_token	*token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->str = malloc((len + 1) * sizeof(char));
	if (token->str == NULL)
	{
		free(token);
		return (NULL);
	}
	token->str[len] = '\0';
	strncpy(token->str, line, len);
	token->lin = lin;
	token->col = col;
	return (token);
}

static size_t	get_len_token(char *line)
{
	if (strncmp(line, LABEL_KEYWORD, strlen(LABEL_KEYWORD)) == 0)
		return (strlen(LABEL_KEYWORD));
	size_t	i = 0;
	while (strchr(IGNORED_CHARS, line[i]) == NULL
		&& strncmp(&line[i], COMMENT_KEYWORD, strlen(COMMENT_KEYWORD)) != 0
		&& strncmp(&line[i], LABEL_KEYWORD, strlen(LABEL_KEYWORD)) != 0)
		i++;
	return (i);
}

static size_t	get_len_until_token(char *line)
{
	size_t	i = 0;
	while (line[i] != '\0' && strchr(IGNORED_CHARS, line[i]) != NULL)
		i++;
	return (i);
}

static bool	tokenize_words(t_data *data, char *line, size_t lin, size_t col)
{
	size_t		i = 0;
	while (line[i] != '\0'
		&& strncmp(&line[i], COMMENT_KEYWORD, strlen(COMMENT_KEYWORD)) != 0)
	{
		size_t	len = get_len_token(&line[i]);
		t_token	*token = tokenize_word(&line[i], len, lin, col + i + 1);
		if (token == NULL
			|| lst_new_back((t_lst **)&(lst_last(data->tokens)->content), token) == 1)
		{
			free(token);
			fprintf(stderr, "%s: %s: %s: %s\n",
				EXECUTABLE_NAME, LIB_LIBC, FUNC_MALLOC, ERROR_FAILED_ALLOC);
			return (1);
		}
		i += len;
		i += get_len_until_token(&line[i]);
	}
	return (0);
}

static bool	tokenize_line(t_data *data, char *line, size_t lin)
{
	size_t	i = get_len_until_token(line);
	if (line[i] == '\0' || strncmp(&line[i], COMMENT_KEYWORD, strlen(COMMENT_KEYWORD)) == 0)
		return (0);
	if (lst_new_back(&data->tokens, NULL) == 1)
	{
		fprintf(stderr, "%s: %s: %s: %s\n",
			EXECUTABLE_NAME, LIB_LIBC, FUNC_MALLOC, ERROR_FAILED_ALLOC);
		return (1);
	}
	if (tokenize_words(data, &line[i], lin, i) == 1)
		return (1);
	return (0);
}

bool	tokenize(t_data *data)
{
	if (file_open(&((t_file *)data->files.arr)[INFILE_CODE], FOPEN_READ_MODE) == 1)
	{
		fprintf(stderr, "%s: %s: %s: %s: \"%s\"\n",
			EXECUTABLE_NAME, LIB_LIBC, FUNC_FOPEN, ERROR_OPEN_FILE,
			((t_file *)data->files.arr)[INFILE_CODE].name);
		return (1);
	}
	char	*line = NULL;
	size_t	lin = 1;
	while (1)
	{
		free(line);
		if (file_get_next_line(&((t_file *)data->files.arr)[INFILE_CODE], &line) == 1)
		{
			fprintf(stderr, "%s: %s: %s: %s: \"%s\"\n",
				EXECUTABLE_NAME, LIB_LIBC, FUNC_GETLINE, ERROR_READ_FILE,
				((t_file *)data->files.arr)[INFILE_CODE].name);
			file_close(&((t_file *)data->files.arr)[INFILE_CODE]);
			return (1);
		}
		if (line == NULL)
		{
			file_close(&((t_file *)data->files.arr)[INFILE_CODE]);
			return (0);
		}
		if (tokenize_line(data, line, lin) == 1)
		{
			free(line);
			file_close(&((t_file *)data->files.arr)[INFILE_CODE]);
			return (1);
		}
		lin++;
	}
}
