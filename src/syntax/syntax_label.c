#include <sys/param.h>
#include "lst.h"
#include "syntax.h"
#include "tokenization.h"
#include "cmp.h"
#include "error.h"

bool	check_label_syntax(t_lst **tokens_ptr)
{
	t_lst*	tokens = *tokens_ptr;
	ssize_t	i = lst_find_index(tokens, LABEL_KEYWORD, cmp_token);
	if (i == -1)
		return (0);
	*tokens_ptr = lst_get_node(tokens, (size_t)i + 1);
	if (i < 1)
	{
		fprintf(stderr, "%s: %s (%zu:%zu): %s: %s\n",
			EXECUTABLE_NAME, ERROR_SYNTAX,
			((t_token *)tokens->content)->lin,
			MAX(((t_token *)tokens->content)->col, (size_t)2) - 1,
			ERROR_LABEL, ERROR_LABEL_TOO_FEW_ARGS);
		return (1);
	}
	if (i > 1)
	{
		tokens = tokens->next;
		fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: ",
			EXECUTABLE_NAME, ERROR_SYNTAX,
			((t_token *)tokens->content)->lin, ((t_token *)tokens->content)->col,
			ERROR_LABEL, ERROR_LABEL_TOO_MANY_ARGS);
		for (size_t i_error = 1; i_error < (size_t)i; i_error++)
		{
			fprintf(stderr, "\"%s\"", ((t_token *)tokens->content)->str);
			if (i_error + 1 < (size_t)i)
				fprintf(stderr, ", ");
			tokens = tokens->next;
		}
		fprintf(stderr, "\n");
		return (1);
	}
	return (0);
}
