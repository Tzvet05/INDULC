#include <stdlib.h>
#include "lst.h"
#include "tokenization.h"

void	free_token(void *token)
{
	free(((token_t *)token)->str);
	free(token);
}

void	free_tokens(lst_t **token_col)
{
	lst_t	*token_lin = *token_col;
	while (token_lin != NULL)
	{
		lst_clear((lst_t **)&token_lin->content, free_token);
		token_lin = token_lin->next;
	}
	lst_clear(token_col, free);
	*token_col = NULL;
}
