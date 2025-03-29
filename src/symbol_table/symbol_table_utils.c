#include <string.h>
#include "get_struct.h"
#include "label.h"
#include "syntax.h"

bool	has_instruction(t_isa* isa, t_lst* tokens)
{
	if (is_label(tokens) == 1)
		tokens = tokens->next->next;
	return (tokens != NULL && get_instruction(isa, ((t_token *)tokens->content)->str) != NULL);
}

bool	is_label(t_lst* tokens)
{
	if (tokens->next == NULL)
		return (0);
	else if (strcmp(((t_token *)tokens->next->content)->str, LABEL_KEYWORD) != 0)
		return (0);
	else
		return (1);
}
