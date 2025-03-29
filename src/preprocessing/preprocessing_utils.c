#include <string.h>
#include <stdbool.h>
#include "lst.h"
#include "syntax.h"
#include "token.h"

bool	is_define(t_lst* tokens)
{
	if (strcmp(((t_token *)tokens->content)->str, DEFINE_KEYWORD) != 0)
		return (0);
	else if (tokens->next == NULL)
		return (0);
	else if (tokens->next->next == NULL)
		return (0);
	else if (tokens->next->next->next != NULL)
		return (0);
	else
		return (1);
}
