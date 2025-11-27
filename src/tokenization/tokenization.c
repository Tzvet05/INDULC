#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "lst.h"
#include "point.h"
#include "data.h"
#include "tokenization.h"
#include "files.h"
#include "syntax.h"
#include "error.h"

static size_t	get_len_until_token(char *line)
{
	size_t	i = 0;
	while (line[i] != '\0' && strchr(IGNORED_CHARS, line[i]) != NULL)
		i++;
	return (i);
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

static t_token	*tokenize_word(char *line, size_t len, t_point *pos)
{
	t_token	*token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->str = strndup(line, len);
	if (token->str == NULL)
	{
		free(token);
		return (NULL);
	}
	token->lin = (size_t)pos->y;
	token->col = (size_t)pos->x;
	return (token);
}

static bool	tokenize_words(t_lst **line_tokens, char *line, t_point *pos)
{
	size_t	i = get_len_until_token(line);
	while (line[i] != '\0' && strncmp(&line[i], COMMENT_KEYWORD, strlen(COMMENT_KEYWORD)) != 0)
	{
		size_t	len = get_len_token(&line[i]);
		pos->x = (ssize_t)i + 1;
		t_token	*token = tokenize_word(&line[i], len, pos);
		if (token == NULL || lst_new_back(line_tokens, token) == 1)
		{
			free_token(token);
			fprintf(stderr, "%s: %s: %s: %s: %s\n",
				EXECUTABLE_NAME, ERROR_FUNCTION, LIB_LIBC, FUNC_MALLOC,
				ERROR_ALLOC);
			return (1);
		}
		i += len;
		i += get_len_until_token(&line[i]);
	}
	return (0);
}

static bool	tokenize_line(t_lst **tokens, char *line, t_point *pos)
{
	t_lst	*line_tokens = NULL;
	if (tokenize_words(&line_tokens, line, pos) == 1)
		return (1);
	if (line_tokens == NULL)
		return (0);
	if (lst_new_back(tokens, line_tokens) == 1)
	{
		fprintf(stderr, "%s: %s: %s: %s: %s\n",
			EXECUTABLE_NAME, ERROR_FUNCTION, LIB_LIBC, FUNC_MALLOC, ERROR_ALLOC);
		return (1);
	}
	return (0);
}

bool	tokenize(t_data *data)
{
	if (file_open(&((t_file *)data->files.arr)[INPUT_CODE], FOPEN_MODE_READ) == 1)
	{
		fprintf(stderr, "%s: %s: %s: %s: %s: \"%s\"\n",
			EXECUTABLE_NAME, ERROR_FUNCTION, LIB_LIBC, FUNC_FOPEN, ERROR_OPEN_FILE,
			((t_file *)data->files.arr)[INPUT_CODE].name);
		return (1);
	}
	char	*line = NULL;
	t_point	pos = {.y = 1, .x = 0};
	while (1)
	{
		free(line);
		if (file_get_next_line(&((t_file *)data->files.arr)[INPUT_CODE], &line) == 1)
		{
			fprintf(stderr, "%s: %s: %s: %s: %s: \"%s\"\n",
				EXECUTABLE_NAME, ERROR_FUNCTION, LIB_LIBC, FUNC_GETLINE,
				ERROR_READ_FILE, ((t_file *)data->files.arr)[INPUT_CODE].name);
			file_close(&((t_file *)data->files.arr)[INPUT_CODE]);
			return (1);
		}
		if (line == NULL)
		{
			file_close(&((t_file *)data->files.arr)[INPUT_CODE]);
			return (0);
		}
		if (tokenize_line(&data->tokens, line, &pos) == 1)
		{
			free(line);
			file_close(&((t_file *)data->files.arr)[INPUT_CODE]);
			return (1);
		}
		pos.y++;
	}
}
