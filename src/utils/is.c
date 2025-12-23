#include <stdbool.h>
#include <string.h>
#include "lst.h"
#include "parr.h"
#include "syntax.h"
#include "tokenization.h"
#include "isa.h"
#include "cmp.h"

bool	is_option(char *str)
{
	return (str[0] == '-');
}

bool	has_parameter(char *str)
{
	return (strchr(str, '=') != NULL);
}

bool	is_define(lst_t *tokens)
{
	return (strcmp(((token_t *)tokens->content)->str, KEYWORD_DEFINE) == 0
		&& tokens->next != NULL && tokens->next->next != NULL
		&& tokens->next->next->next == NULL);
}

bool	is_label(lst_t *tokens)
{
	return (tokens->next != NULL
		&& strcmp(((token_t *)tokens->next->content)->str, KEYWORD_LABEL) == 0);
}

bool	has_instruction(isa_t *isa, lst_t *tokens)
{
	if (is_label(tokens) == 1)
		tokens = tokens->next->next;
	return (tokens != NULL && parr_find(&isa->instructions, ((token_t *)tokens->content)->str,
		cmp_mnemonics) != NULL);
}
