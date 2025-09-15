#include <string.h>
#include "lst.h"
#include "syntax.h"
#include "tokenization.h"

bool	is_define(t_lst* tokens)
{
	return (strcmp(((t_token *)tokens->content)->str, DEFINE_KEYWORD) == 0
		&& tokens->next != NULL && tokens->next->next != NULL
		&& tokens->next->next->next == NULL);
}
