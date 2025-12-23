#include "lst.h"
#include "tokenization.h"
#include "symbol_table.h"
#include "cmp.h"
#include "nbr.h"

ssize_t	get_immediate_operand(lst_t *symbol_table, token_t *token)
{
	lst_t	*label = lst_find(symbol_table, token->str, cmp_label);
	if (label != NULL)
		return ((ssize_t)((label_t *)label->content)->line);
	return (get_number(token->str));
}
