#include "indulc.h"
#include "label.h"
#include "error.h"

static bool	add_label(t_lst* tokens, t_lst** symbol_table, size_t line)
{
	t_lst*	existing_label = lst_find(*symbol_table,
		((t_token *)tokens->content)->str, cmp_label);
	if (existing_label != NULL)
	{
		fprintf(stderr, "%s: %s (%zu:%zu): %s: \"%s\" (previously declared at %zu:%zu)\n",
			EXECUTABLE_NAME, ERROR_SYNTAX, ((t_token *)tokens->content)->lin,
			((t_token *)tokens->content)->col, ERROR_LABEL_DUPLICATE,
			((t_token *)tokens->content)->str,
			((t_label *)existing_label->content)->name->lin,
			((t_label *)existing_label->content)->name->col);
		return (1);
	}
	else
	{
		t_label*	label = malloc(sizeof(t_label));
		if (label == NULL)
			return (1);
		label->name = (t_token *)tokens->content;
		if (tokens->next->next == NULL)
			label->line = line + 1;
		else
			label->line = line;
		if (lst_new_back(symbol_table, label) == 1)
		{
			free_label(label);
			return (1);
		}
	}
	return (0);
}

bool	build_symbol_table(t_data* data)
{
	size_t	line = 0;
	t_lst*	tokens = data->tokens;
	while (tokens != NULL)
	{
		if (is_label((t_lst *)tokens->content) == 1
			&& add_label((t_lst *)tokens->content, &data->symbol_table, line) == 1)
		{
			fprintf(stderr, "%s: %s: %s\n",
				EXECUTABLE_NAME, FUNC_MALLOC, ERROR_FAILED_ALLOC);
			return (1);
		}
		if (has_instruction(&data->isa, (t_lst *)tokens->content) == 1)
			line++;
		tokens = tokens->next;
	}
	return (0);
}
