#include "data.h"
#include "syntax.h"
#include "token.h"
#include "error.h"

static bool	check_remaining_tokens_syntax(t_lst** tokens_ptr)
{
	t_lst*	tokens = *tokens_ptr;
	while (tokens != NULL)
	{
		fprintf(stderr, "%s: %s (%zu:%zu): %s: \"%s\"\n",
			EXECUTABLE_NAME, ERROR_SYNTAX, ((t_token *)tokens->content)->lin,
			((t_token *)tokens->content)->col, ERROR_TOKEN,
			((t_token *)tokens->content)->str);
		tokens = tokens->next;
	}
	*tokens_ptr = tokens;
	return (1);
}

bool	analyse_syntax(t_data *data)
{
	bool	error = 0;
	t_lst*	tokens_lin = data->tokens;
	while (tokens_lin != NULL)
	{
		t_lst*	tokens_col = (t_lst *)tokens_lin->content;
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
