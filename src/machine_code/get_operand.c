#include "lst.h"
#include "tokenization.h"
#include "symbol_table.h"
#include "cmp.h"
#include "nbr.h"

ssize_t	get_immediate_operand(t_lst* symbol_table, t_token* token)
{
	t_lst*	label = lst_find(symbol_table, token->str, cmp_label);
	if (label != NULL)
		return ((ssize_t)((t_label *)label->content)->line);
	return (get_number(token->str));
}
