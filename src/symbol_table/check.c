#include "lst.h"
#include "data.h"
#include "tokenization.h"
#include "symbol_table.h"
#include "cmp.h"
#include "is.h"
#include "error.h"

bool	check_label(t_lst *tokens, t_lst *symbol_table)
{
	t_lst	*label = lst_find(symbol_table, ((t_token *)tokens->content)->str, cmp_label);
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

void	check_labels(t_data *data)
{
	t_lst	*token_lin = data->tokens;
	while (token_lin != NULL)
	{
		t_lst	*token_col = token_lin->content;
		while (token_col != NULL)
		{
			t_lst	*label = lst_find(data->symbol_table,
				((t_token *)token_col->content)->str, cmp_label);
			if (label != NULL)
				((t_label *)label->content)->n_uses++;
			token_col = token_col->next;
		}
		token_lin = token_lin->next;
	}
	t_lst	*label = data->symbol_table;
	while (label != NULL)
	{
		if (((t_label *)label->content)->n_uses <= 1)
			fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: \"%s\"\n",
				EXECUTABLE_NAME, WARNING_SYNTAX,
				((t_label *)label->content)->name->lin,
				((t_label *)label->content)->name->col, WARNING_LABEL,
				WARNING_LABEL_UNUSED, ((t_label *)label->content)->name->str);
		label = label->next;
	}
}
