#include "error.h"
#include "syntax.h"
#include "token.h"
#include "cmp.h"
#include "lst.h"

bool	check_label_syntax(t_lst **tokens_ptr)
{
	bool	error = 0;
	t_lst*	tokens = *tokens_ptr;
	ssize_t	i = lst_find_index(tokens, LABEL_KEYWORD, cmp_token);
	if (i == -1)
		return (0);
	*tokens_ptr = lst_get_node(tokens, i + 1);
	if (i < 1)
	{
		fprintf(stderr, "%s: %s (%zu:%zu): %s: %s\n",
			EXECUTABLE_NAME, ERROR_SYNTAX,
			((t_token *)tokens->content)->lin, ((t_token *)tokens->content)->col,
			ERROR_LABEL, ERROR_LABEL_TOO_FEW_ARGS);
		return (1);
	}
	tokens = tokens->next;
	for (size_t i_error = 1; i_error < (size_t)i; i_error++)
	{
		fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: \"%s\"\n",
			EXECUTABLE_NAME, ERROR_SYNTAX,
			((t_token *)tokens->content)->lin, ((t_token *)tokens->content)->col,
			ERROR_LABEL, ERROR_LABEL_TOO_MANY_ARGS, ((t_token *)tokens->content)->str);
		error = 1;
		tokens = tokens->next;
	}
	return (error);
}
