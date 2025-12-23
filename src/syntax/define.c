#include <string.h>
#include "lst.h"
#include "data.h"
#include "tokenization.h"
#include "arguments.h"
#include "syntax.h"
#include "cmp.h"
#include "nbr.h"
#include "error.h"

static void	check_define_identifier(data_t *data, lst_t *tokens)
{
	if (strcmp(((token_t *)tokens->next->content)->str,
		((token_t *)tokens->next->next->content)->str) == 0)
		fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: \"%s\"\n",
			EXECUTABLE_NAME, WARNING_SYNTAX, ((token_t *)tokens->next->content)->lin,
			((token_t *)tokens->next->content)->col, WARNING_DEFINE,
			WARNING_DEFINE_USELESS, ((token_t *)tokens->next->content)->str);
	if (data->options[OPTION_MACRO_WARNINGS] == PARAM_YES)
	{
		if (parr_find(&data->isa.flags, ((token_t *)tokens->next->content)->str,
			cmp_mnemonics) != NULL)
			fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: \"%s\"\n",
				EXECUTABLE_NAME, WARNING_SYNTAX,
				((token_t *)tokens->next->content)->lin,
				((token_t *)tokens->next->content)->col, WARNING_DEFINE,
				WARNING_DEFINE_FLAG, ((token_t *)tokens->next->content)->str);
		if (parr_find(&data->isa.instructions, ((token_t *)tokens->next->content)->str,
			cmp_mnemonics) != NULL)
			fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: \"%s\"\n",
				EXECUTABLE_NAME, WARNING_SYNTAX,
				((token_t *)tokens->next->content)->lin,
				((token_t *)tokens->next->content)->col,
				WARNING_DEFINE, WARNING_DEFINE_INSTRUCTION,
				((token_t *)tokens->next->content)->str);
		if (parr_find(&data->isa.registers, ((token_t *)tokens->next->content)->str,
			cmp_mnemonics) != NULL)
			fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: \"%s\"\n",
				EXECUTABLE_NAME, WARNING_SYNTAX,
				((token_t *)tokens->next->content)->lin,
				((token_t *)tokens->next->content)->col, WARNING_DEFINE,
				WARNING_DEFINE_REGISTER, ((token_t *)tokens->next->content)->str);
		if (is_number(((token_t *)tokens->next->content)->str) == 1)
			fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: \"%s\"\n",
				EXECUTABLE_NAME, WARNING_SYNTAX,
				((token_t *)tokens->next->content)->lin,
				((token_t *)tokens->next->content)->col, WARNING_DEFINE,
				WARNING_DEFINE_NUMBER, ((token_t *)tokens->next->content)->str);
		if (strcmp(((token_t *)tokens->next->content)->str, KEYWORD_DEFINE) == 0)
			fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: \"%s\"\n",
				EXECUTABLE_NAME, WARNING_SYNTAX,
				((token_t *)tokens->next->content)->lin,
				((token_t *)tokens->next->content)->col, WARNING_DEFINE,
				WARNING_DEFINE_DEFINE, ((token_t *)tokens->next->content)->str);
		if (strcmp(((token_t *)tokens->next->content)->str, KEYWORD_LABEL) == 0)
			fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: \"%s\"\n",
				EXECUTABLE_NAME, WARNING_SYNTAX,
				((token_t *)tokens->next->content)->lin,
				((token_t *)tokens->next->content)->col, WARNING_DEFINE,
				WARNING_DEFINE_LABEL, ((token_t *)tokens->next->content)->str);
	}
}

bool	check_define_syntax(data_t *data, lst_t **tokens_ptr)
{
	lst_t	*tokens = *tokens_ptr;
	if (strcmp(((token_t *)tokens->content)->str, KEYWORD_DEFINE) != 0)
		return (0);
	lst_t	*tokens_first = tokens;
	*tokens_ptr = lst_last(tokens)->next;
	if (tokens->next == NULL)
	{
		fprintf(stderr, "%s: %s (%zu:%zu): %s: %s\n",
			EXECUTABLE_NAME, ERROR_SYNTAX,
			((token_t *)tokens->content)->lin,
			((token_t *)tokens->content)->col
				+ strlen(((token_t *)tokens->content)->str) + 1,
			ERROR_DEFINE, ERROR_DEFINE_TOO_FEW_ARGS);
		return (1);
	}
	tokens = tokens->next;
	if (tokens->next == NULL)
	{
		fprintf(stderr, "%s: %s (%zu:%zu): %s: %s\n",
			EXECUTABLE_NAME, ERROR_SYNTAX,
			((token_t *)tokens->content)->lin,
			((token_t *)tokens->content)->col
				+ strlen(((token_t *)tokens->content)->str) + 1,
			ERROR_DEFINE, ERROR_DEFINE_TOO_FEW_ARGS);
		return (1);
	}
	tokens = tokens->next;
	if (is_number(((token_t *)tokens->content)->str) == 1
		&& will_overflow_str(((token_t *)tokens->content)->str,
			data->isa.instruction_length) == 1)
		fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: \"%s\"\n",
			EXECUTABLE_NAME, WARNING_SYNTAX,
			((token_t *)tokens->content)->lin, ((token_t *)tokens->content)->col,
			WARNING_DEFINE, WARNING_OVERFLOW, ((token_t *)tokens->content)->str);
	tokens = tokens->next;
	if (tokens != NULL)
	{
		fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: ",
			EXECUTABLE_NAME, ERROR_SYNTAX,
			((token_t *)tokens->content)->lin, ((token_t *)tokens->content)->col,
			ERROR_DEFINE, ERROR_DEFINE_TOO_MANY_ARGS);
		while (tokens != NULL)
		{
			fprintf(stderr, "\"%s\"", ((token_t *)tokens->content)->str);
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
