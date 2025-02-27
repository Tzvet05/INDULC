#include <string.h>
#include <ctype.h>
#include "indulc.h"
#include "error.h"
#include "nbr.h"

bool	check_define_syntax(t_lst **tokens_ptr)
{
	bool	error = 0;
	t_lst*	tokens = *tokens_ptr;
	if (strcmp(((t_token *)tokens->content)->str, DEFINE_KEYWORD) != 0)
		return (0);
	*tokens_ptr = lst_get_node(tokens, 3);
	if (tokens->next == NULL)
	{
		fprintf(stderr, "%s: %s (%zu:%zu): %s: %s\n",
			EXECUTABLE_NAME, ERROR_SYNTAX,
			((t_token *)tokens->content)->lin,
			((t_token *)tokens->content)->col
				+ strlen(((t_token *)tokens->content)->str) + 1,
			ERROR_DEFINE, ERROR_DEFINE_TOO_FEW_ARGS);
		return (1);
	}
	tokens = tokens->next;
	if (isalpha(((t_token *)tokens->content)->str[0]) == 0)
	{
		fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: \"%s\"\n",
			EXECUTABLE_NAME, ERROR_SYNTAX,
			((t_token *)tokens->content)->lin, ((t_token *)tokens->content)->col,
			ERROR_DEFINE, ERROR_DEFINE_INVALID_NAME, ((t_token *)tokens->content)->str);
		error = 1;
	}
	if (tokens->next == NULL)
	{
		fprintf(stderr, "%s: %s (%zu:%zu): %s: %s\n",
			EXECUTABLE_NAME, ERROR_SYNTAX,
			((t_token *)tokens->content)->lin,
			((t_token *)tokens->content)->col
				+ strlen(((t_token *)tokens->content)->str) + 1,
			ERROR_DEFINE, ERROR_DEFINE_TOO_FEW_ARGS);
		return (1);
	}
	tokens = tokens->next;
	if (is_number(((t_token *)tokens->content)->str) == 0)
	{
		fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: \"%s\"\n",
			EXECUTABLE_NAME, ERROR_SYNTAX,
			((t_token *)tokens->content)->lin, ((t_token *)tokens->content)->col,
			ERROR_DEFINE, ERROR_NOT_NUMBER, ((t_token *)tokens->content)->str);
		error = 1;
	}
	if (will_overflow_str(((t_token *)tokens->content)->str, 16) == 1)
		fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: \"%s\"\n",
			EXECUTABLE_NAME, WARNING_SYNTAX,
			((t_token *)tokens->content)->lin, ((t_token *)tokens->content)->col,
			WARNING_DEFINE, WARNING_OVERFLOW, ((t_token *)tokens->content)->str);
	tokens = tokens->next;
	if (tokens != NULL)
	{
		fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: \"%s\"\n",
			EXECUTABLE_NAME, ERROR_SYNTAX,
			((t_token *)tokens->content)->lin, ((t_token *)tokens->content)->col,
			ERROR_DEFINE, ERROR_DEFINE_TOO_MANY_ARGS,
			((t_token *)tokens->content)->str);
		return (1);
	}
	return (error);
}
