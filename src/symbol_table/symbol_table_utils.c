#include <string.h>
#include "lst.h"
#include "tokenization.h"
#include "isa.h"
#include "syntax.h"
#include "cmp.h"

bool	is_label(t_lst* tokens)
{
	return (tokens->next != NULL
		&& strcmp(((t_token *)tokens->next->content)->str, LABEL_KEYWORD) == 0);
}

bool	has_instruction(t_isa* isa, t_lst* tokens)
{
	if (is_label(tokens) == 1)
		tokens = tokens->next->next;
	return (tokens != NULL
		&& parr_find(&isa->instructions, ((t_token *)tokens->content)->str, cmp_mnemonics));
}
