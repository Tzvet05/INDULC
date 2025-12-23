#include "lst.h"
#include "data.h"
#include "tokenization.h"
#include "symbol_table.h"
#include "cmp.h"
#include "is.h"
#include "error.h"

bool	check_label(lst_t *tokens, lst_t *symbol_table)
{
	lst_t	*label = lst_find(symbol_table, ((token_t *)tokens->content)->str, cmp_label);
	if (label != NULL)
	{
		fprintf(stderr, "%s: %s (%zu:%zu): %s: \"%s\" (previously declared at %zu:%zu)\n",
			EXECUTABLE_NAME, ERROR_SYNTAX, ((token_t *)tokens->content)->lin,
			((token_t *)tokens->content)->col, ERROR_LABEL_DUPLICATE,
			((token_t *)tokens->content)->str, ((label_t *)label->content)->name->lin,
			((label_t *)label->content)->name->col);
		return (1);
	}
	return (0);
}

void	check_labels(data_t *data)
{
	lst_t	*token_lin = data->tokens;
	while (token_lin != NULL)
	{
		lst_t	*token_col = token_lin->content;
		while (token_col != NULL)
		{
			lst_t	*label = lst_find(data->symbol_table,
				((token_t *)token_col->content)->str, cmp_label);
			if (label != NULL)
				((label_t *)label->content)->n_uses++;
			token_col = token_col->next;
		}
		token_lin = token_lin->next;
	}
	lst_t	*label = data->symbol_table;
	while (label != NULL)
	{
		if (((label_t *)label->content)->n_uses <= 1)
			fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: \"%s\"\n",
				EXECUTABLE_NAME, WARNING_SYNTAX,
				((label_t *)label->content)->name->lin,
				((label_t *)label->content)->name->col, WARNING_LABEL,
				WARNING_LABEL_UNUSED, ((label_t *)label->content)->name->str);
		label = label->next;
	}
}
