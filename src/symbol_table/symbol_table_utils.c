#include <string.h>
#include <ctype.h>
#include "indulc.h"

bool	has_instruction(t_isa* isa, t_lst* tokens)
{
	if (is_label(tokens) == 1)
		tokens = tokens->next->next;
	return (tokens != NULL && get_assembling_target(isa, ((t_token *)tokens->content)->str,
		INSTRUCTION) != NULL);
}

bool	is_label(t_lst* tokens)
{
	if (tokens->next == NULL)
		return (0);
	else if (strcmp(((t_token *)tokens->next->content)->str, LABEL_KEYWORD) != 0)
		return (0);
	else if (isalpha(((t_token *)tokens->content)->str[0]) == 0)
		return (0);
	else
		return (1);
}
