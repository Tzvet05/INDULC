#include <stdlib.h>
#include "token.h"
#include "lst.h"

void	free_token(void* token)
{
	free(((t_token *)token)->str);
	free(token);
}

void	free_tokens(t_lst* token_col)
{
	t_lst*	token_lin;
	token_lin = token_col;
	while (token_lin != NULL)
	{
		lst_clear((t_lst **)&(token_lin->content), free_token);
		token_lin = token_lin->next;
	}
	lst_clear(&token_col, free);
}
