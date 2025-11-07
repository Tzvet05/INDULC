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

bool	is_define(t_lst *tokens)
{
	return (strcmp(((t_token *)tokens->content)->str, DEFINE_KEYWORD) == 0
		&& tokens->next != NULL && tokens->next->next != NULL
		&& tokens->next->next->next == NULL);
}

bool	is_label(t_lst *tokens)
{
	return (tokens->next != NULL
		&& strcmp(((t_token *)tokens->next->content)->str, LABEL_KEYWORD) == 0);
}

bool	has_instruction(t_isa *isa, t_lst *tokens)
{
	if (is_label(tokens) == 1)
		tokens = tokens->next->next;
	return (tokens != NULL && parr_find(&isa->instructions, ((t_token *)tokens->content)->str,
		cmp_mnemonics) != NULL);
}
