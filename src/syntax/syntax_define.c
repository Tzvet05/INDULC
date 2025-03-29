#include <string.h>
#include "error.h"
#include "token.h"
#include "syntax.h"
#include "get_struct.h"
#include "nbr.h"

#ifndef COMP_MUTE_MACRO_WARNINGS
static void	check_define_identifier(t_isa* isa, t_lst* tokens)
{
	if (strcmp(((t_token *)tokens->next->content)->str,
		((t_token *)tokens->next->next->content)->str) == 0)
	{
		fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: \"%s\"\n",
			EXECUTABLE_NAME, WARNING_SYNTAX, ((t_token *)tokens->next->content)->lin,
			((t_token *)tokens->next->content)->col, WARNING_DEFINE,
			WARNING_DEFINE_USELESS, ((t_token *)tokens->next->content)->str);
		return;
	}
	if (get_flag(isa, ((t_token *)tokens->next->content)->str) != NULL)
		fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: \"%s\"\n",
			EXECUTABLE_NAME, WARNING_SYNTAX, ((t_token *)tokens->next->content)->lin,
			((t_token *)tokens->next->content)->col, WARNING_DEFINE,
			WARNING_DEFINE_FLAG, ((t_token *)tokens->next->content)->str);
	if (get_instruction(isa, ((t_token *)tokens->next->content)->str) != NULL)
		fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: \"%s\"\n",
			EXECUTABLE_NAME, WARNING_SYNTAX, ((t_token *)tokens->next->content)->lin,
			((t_token *)tokens->next->content)->col, WARNING_DEFINE,
			WARNING_DEFINE_INSTRUCTION, ((t_token *)tokens->next->content)->str);
	if (get_register(isa, ((t_token *)tokens->next->content)->str) != NULL)
		fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: \"%s\"\n",
			EXECUTABLE_NAME, WARNING_SYNTAX, ((t_token *)tokens->next->content)->lin,
			((t_token *)tokens->next->content)->col, WARNING_DEFINE,
			WARNING_DEFINE_REGISTER, ((t_token *)tokens->next->content)->str);
	if (is_number(((t_token *)tokens->next->content)->str) == 1)
		fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: \"%s\"\n",
			EXECUTABLE_NAME, WARNING_SYNTAX, ((t_token *)tokens->next->content)->lin,
			((t_token *)tokens->next->content)->col, WARNING_DEFINE,
			WARNING_DEFINE_NUMBER, ((t_token *)tokens->next->content)->str);
	if (strncmp(((t_token *)tokens->next->content)->str, LABEL_KEYWORD, strlen(LABEL_KEYWORD))
		== 0)
		fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: \"%s\"\n",
			EXECUTABLE_NAME, WARNING_SYNTAX, ((t_token *)tokens->next->content)->lin,
			((t_token *)tokens->next->content)->col, WARNING_DEFINE,
			WARNING_DEFINE_LABEL, ((t_token *)tokens->next->content)->str);
}
#endif

bool	check_define_syntax(t_isa* isa, t_lst **tokens_ptr)
{
	bool	error = 0;
	t_lst*	tokens = *tokens_ptr;
	if (strcmp(((t_token *)tokens->content)->str, DEFINE_KEYWORD) != 0)
		return (0);
#ifndef COMP_MUTE_MACRO_WARNINGS
	t_lst*	tokens_first = tokens;
#endif
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
	if (is_number(((t_token *)tokens->content)->str) == 1
		&& will_overflow_str(((t_token *)tokens->content)->str,
			isa->instruction_length) == 1)
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
#ifndef COMP_MUTE_MACRO_WARNINGS
	check_define_identifier(isa, tokens_first);
#endif
	return (error);
}
