#include "lst.h"
#include "data.h"
#include "syntax.h"
#include "tokenization.h"
#include "error.h"

static bool	check_remaining_tokens_syntax(lst_t **tokens_ptr)
{
	lst_t	*tokens = *tokens_ptr;
	fprintf(stderr, "%s: %s (%zu:%zu): %s: ",
		EXECUTABLE_NAME, ERROR_SYNTAX,
		((token_t *)tokens->content)->lin, ((token_t *)tokens->content)->col, ERROR_TOKEN);
	while (tokens != NULL)
	{
		fprintf(stderr, "\"%s\"", ((token_t *)tokens->content)->str);
		if (tokens->next != NULL)
			fprintf(stderr, ", ");
		tokens = tokens->next;
	}
	fprintf(stderr, "\n");
	*tokens_ptr = tokens;
	return (1);
}

bool	analyse_syntax(data_t *data)
{
	bool	error = 0;
	lst_t	*tokens_lin = data->tokens;
	while (tokens_lin != NULL)
	{
		lst_t	*tokens_col = tokens_lin->content;
		if (tokens_col != NULL && check_define_syntax(data, &tokens_col) == 1)
			error = 1;
		if (tokens_col != NULL && check_label_syntax(&tokens_col) == 1)
			error = 1;
		if (tokens_col != NULL && check_instruction_syntax(data, &tokens_col) == 1)
			error = 1;
		if (tokens_col != NULL && check_remaining_tokens_syntax(&tokens_col) == 1)
			error = 1;
		tokens_lin = tokens_lin->next;
	}
	return (error);
}
