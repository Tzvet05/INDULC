#include <stdlib.h>
#include "lst.h"
#include "point.h"
#include "data.h"
#include "tokenization.h"
#include "symbol_table.h"
#include "cmp.h"
#include "is.h"
#include "error.h"

static bool	add_label(lst_t *tokens, lst_t **symbol_table, point_t *pos)
{
	label_t	*new_label = malloc(sizeof(label_t));
	if (new_label == NULL)
		return (1);
	new_label->name = tokens->content;
	new_label->line = (size_t)pos->y;
	new_label->n_uses = 0;
	if (lst_new_back(symbol_table, new_label) == 1)
	{
		free_label(new_label);
		return (1);
	}
	return (0);
}

bool	build_symbol_table(data_t *data)
{
	point_t	pos = {0};
	lst_t	*tokens = data->tokens;
	while (tokens != NULL)
	{
		if (is_label(tokens->content) == 1)
		{
			if (check_label(tokens->content, data->symbol_table) == 1)
				return (1);
			if (add_label(tokens->content, &data->symbol_table, &pos) == 1)
			{
				fprintf(stderr, "%s: %s: %s: %s: %s\n",
					EXECUTABLE_NAME, ERROR_FUNCTION, LIB_LIBC, FUNC_MALLOC,
					ERROR_ALLOC);
				return (1);
			}
		}
		if (has_instruction(&data->isa, tokens->content) == 1)
			pos.y++;
		tokens = tokens->next;
	}
	check_labels(data);
	return (0);
}
