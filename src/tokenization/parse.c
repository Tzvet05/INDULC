#include <string.h>
#include "parr.h"
#include "syntax.h"

t_keyword	*parse_keyword(const t_parr *keywords, char *line, size_t i_char)
{
	t_keyword	*keyword_match = NULL;
	size_t	len_match = 0;
	for (size_t i_keyword = 0; i_keyword < keywords->len; i_keyword++)
	{
		t_keyword	*keyword = &((t_keyword *)keywords->arr)[i_keyword];
		if (strlen(keyword->str) > len_match
			&& strncmp(&line[i_char], keyword->str, strlen(keyword->str)) == 0
			&& (GET_PARSING(keyword->info) != SPACED
			|| ((i_char == 0 || strchr(IGNORED_CHARS, line[i_char - 1]) != NULL)
			&& strchr(IGNORED_CHARS, line[i_char + strlen(keyword->str)]) != NULL)))
		{
			keyword_match = keyword;
			len_match = strlen(keyword_match->str);
		}
	}
	return (keyword_match);
}
