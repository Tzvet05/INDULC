#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "lst.h"
#include "pstr.h"
#include "point.h"
#include "data.h"
#include "tokenization.h"
#include "files.h"
#include "syntax.h"
#include "cmp.h"
#include "error.h"

static size_t	get_len_ignore(char *line)
{
	size_t	i = 0;
	while (line[i] != '\0' && strchr(IGNORED_CHARS, line[i]) != NULL)
		i++;
	return (i);
}

static size_t	get_len_token(const t_parr *keywords, char *line)
{
	t_keyword	*keyword = NULL;
	size_t	i = 0;
	while (keyword == NULL && strchr(IGNORED_CHARS, line[i]) == NULL)
	{
		i++;
		keyword = parse_keyword(keywords, line, i);
	}
	return (i);
}

static t_token	*tokenize_word(t_pstr *word, t_point *pos)
{
	t_token	*token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->str = strndup(word->str, word->len);
	if (token->str == NULL)
	{
		free(token);
		return (NULL);
	}
	token->lin = (size_t)pos->y + 1;
	token->col = (size_t)pos->x + 1;
	return (token);
}

static bool	tokenize_words(const t_parr *keywords, t_lst **line_tokens, char *line,
	t_point *pos)
{
	t_pstr	word = {.str = &line[pos->x], .len = 0};
	pos->x += word.len + get_len_ignore(&word.str[word.len]);
	word.str = &line[pos->x];
	t_keyword	*keyword = parse_keyword(keywords, line, (size_t)pos->x);
	if (keyword != NULL)
		word.len = strlen(keyword->str);
	else
		word.len = get_len_token(keywords, word.str);
	while (word.len > 0 && (keyword == NULL || GET_BEHAVIOR(keyword->info) != PARSE_STOP))
	{
		t_token	*token = tokenize_word(&word, pos);
		if (token == NULL || lst_new_back(line_tokens, token) == 1)
		{
			free_token(token);
			fprintf(stderr, "%s: %s: %s: %s: %s\n",
				EXECUTABLE_NAME, ERROR_FUNCTION, LIB_LIBC, FUNC_MALLOC,
				ERROR_ALLOC);
			return (1);
		}
		pos->x += word.len + get_len_ignore(&word.str[word.len]);
		word.str = &line[pos->x];
		keyword = parse_keyword(keywords, line, (size_t)pos->x);
		if (keyword != NULL)
			word.len = strlen(keyword->str);
		else
			word.len = get_len_token(keywords, word.str);
	}
	return (0);
}

static bool	tokenize_line(const t_parr *keywords, t_lst **tokens, char *line, t_point *pos)
{
	t_lst	*line_tokens = NULL;
	if (tokenize_words(keywords, &line_tokens, line, pos) == 1)
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
	const t_parr	keywords = KEYWORDS;
	char	*line = NULL;
	t_point	pos = {0};
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
		if (tokenize_line(&keywords, &data->tokens, line, &pos) == 1)
		{
			free(line);
			file_close(&((t_file *)data->files.arr)[INPUT_CODE]);
			return (1);
		}
		pos.y++;
		pos.x = 0;
	}
}
