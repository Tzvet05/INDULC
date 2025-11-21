#include <string.h>
#include "lst.h"
#include "data.h"
#include "tokenization.h"
#include "arguments.h"
#include "syntax.h"
#include "cmp.h"
#include "nbr.h"
#include "error.h"

static void	check_define_identifier(t_data *data, t_lst *tokens)
{
	if (strcmp(((t_token *)tokens->next->content)->str,
		((t_token *)tokens->next->next->content)->str) == 0)
		fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: \"%s\"\n",
			EXECUTABLE_NAME, WARNING_SYNTAX, ((t_token *)tokens->next->content)->lin,
			((t_token *)tokens->next->content)->col, WARNING_DEFINE,
			WARNING_DEFINE_USELESS, ((t_token *)tokens->next->content)->str);
	if (data->options[OPTION_MACRO_WARNINGS] == PARAM_YES)
	{
		if (parr_find(&data->isa.flags, ((t_token *)tokens->next->content)->str,
			cmp_mnemonics) != NULL)
			fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: \"%s\"\n",
				EXECUTABLE_NAME, WARNING_SYNTAX,
				((t_token *)tokens->next->content)->lin,
				((t_token *)tokens->next->content)->col, WARNING_DEFINE,
				WARNING_DEFINE_FLAG, ((t_token *)tokens->next->content)->str);
		if (parr_find(&data->isa.instructions, ((t_token *)tokens->next->content)->str,
			cmp_mnemonics) != NULL)
			fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: \"%s\"\n",
				EXECUTABLE_NAME, WARNING_SYNTAX,
				((t_token *)tokens->next->content)->lin,
				((t_token *)tokens->next->content)->col,
				WARNING_DEFINE, WARNING_DEFINE_INSTRUCTION,
				((t_token *)tokens->next->content)->str);
		if (parr_find(&data->isa.registers, ((t_token *)tokens->next->content)->str,
			cmp_mnemonics) != NULL)
			fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: \"%s\"\n",
				EXECUTABLE_NAME, WARNING_SYNTAX,
				((t_token *)tokens->next->content)->lin,
				((t_token *)tokens->next->content)->col, WARNING_DEFINE,
				WARNING_DEFINE_REGISTER, ((t_token *)tokens->next->content)->str);
		if (is_number(((t_token *)tokens->next->content)->str) == 1)
			fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: \"%s\"\n",
				EXECUTABLE_NAME, WARNING_SYNTAX,
				((t_token *)tokens->next->content)->lin,
				((t_token *)tokens->next->content)->col, WARNING_DEFINE,
				WARNING_DEFINE_NUMBER, ((t_token *)tokens->next->content)->str);
		if (strcmp(((t_token *)tokens->next->content)->str, DEFINE_KEYWORD) == 0)
			fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: \"%s\"\n",
				EXECUTABLE_NAME, WARNING_SYNTAX,
				((t_token *)tokens->next->content)->lin,
				((t_token *)tokens->next->content)->col, WARNING_DEFINE,
				WARNING_DEFINE_DEFINE, ((t_token *)tokens->next->content)->str);
		if (strcmp(((t_token *)tokens->next->content)->str, LABEL_KEYWORD) == 0)
			fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: \"%s\"\n",
				EXECUTABLE_NAME, WARNING_SYNTAX,
				((t_token *)tokens->next->content)->lin,
				((t_token *)tokens->next->content)->col, WARNING_DEFINE,
				WARNING_DEFINE_LABEL, ((t_token *)tokens->next->content)->str);
	}
}

bool	check_define_syntax(t_data *data, t_lst **tokens_ptr)
{
	t_lst	*tokens = *tokens_ptr;
	if (strcmp(((t_token *)tokens->content)->str, DEFINE_KEYWORD) != 0)
		return (0);
	t_lst	*tokens_first = tokens;
	*tokens_ptr = lst_last(tokens)->next;
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
			data->isa.instruction_length) == 1)
		fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: \"%s\"\n",
			EXECUTABLE_NAME, WARNING_SYNTAX,
			((t_token *)tokens->content)->lin, ((t_token *)tokens->content)->col,
			WARNING_DEFINE, WARNING_OVERFLOW, ((t_token *)tokens->content)->str);
	tokens = tokens->next;
	if (tokens != NULL)
	{
		fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: ",
			EXECUTABLE_NAME, ERROR_SYNTAX,
			((t_token *)tokens->content)->lin, ((t_token *)tokens->content)->col,
			ERROR_DEFINE, ERROR_DEFINE_TOO_MANY_ARGS);
		while (tokens != NULL)
		{
			fprintf(stderr, "\"%s\"", ((t_token *)tokens->content)->str);
			if (tokens->next != NULL)
				fprintf(stderr, ", ");
			tokens = tokens->next;
		}
		fprintf(stderr, "\n");
		return (1);
	}
	check_define_identifier(data, tokens_first);
	return (0);
}
