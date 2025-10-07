#include <stdlib.h>
#include "lst.h"
#include "data.h"
#include "symbol_table.h"
#include "cmp.h"
#include "error.h"

static bool	check_label(t_lst* tokens, t_lst* symbol_table)
{
	t_lst*	label = lst_find(symbol_table, ((t_token *)tokens->content)->str, cmp_label);
	if (label != NULL)
	{
		fprintf(stderr, "%s: %s (%zu:%zu): %s: \"%s\" (previously declared at %zu:%zu)\n",
			EXECUTABLE_NAME, ERROR_SYNTAX, ((t_token *)tokens->content)->lin,
			((t_token *)tokens->content)->col, ERROR_LABEL_DUPLICATE,
			((t_token *)tokens->content)->str, ((t_label *)label->content)->name->lin,
			((t_label *)label->content)->name->col);
		return (1);
	}
	return (0);
}

static bool	add_label(t_lst* tokens, t_lst** symbol_table, size_t line)
{
	t_label*	new_label = malloc(sizeof(t_label));
	if (new_label == NULL)
		return (1);
	new_label->name = (t_token *)tokens->content;
	new_label->line = line;
	if (lst_new_back(symbol_table, new_label) == 1)
	{
		free_label(new_label);
		return (1);
	}
	return (0);
}

bool	build_symbol_table(t_data* data)
{
	size_t	line = 0;
	t_lst*	tokens = data->tokens;
	while (tokens != NULL)
	{
		if (is_label((t_lst *)tokens->content) == 1)
		{
			if (check_label((t_lst *)tokens->content, data->symbol_table) == 1)
				return (1);
			if (add_label((t_lst *)tokens->content, &data->symbol_table, line) == 1)
			{
				fprintf(stderr, "%s: %s: %s: %s\n",
					EXECUTABLE_NAME, LIB_LIBC, FUNC_MALLOC, ERROR_FAILED_ALLOC);
				return (1);
			}
		}
		if (has_instruction(&data->isa, (t_lst *)tokens->content) == 1)
			line++;
		tokens = tokens->next;
	}
	return (0);
}
