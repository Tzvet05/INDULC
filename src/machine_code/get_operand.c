#include <ctype.h>
#include "indulc.h"
#include "label.h"
#include "nbr.h"

ssize_t	get_register_operand(t_token* token)
{
	size_t	i = 0;
	if (tolower(token->str[i]) == 'r')
		i++;
	return (get_number(&token->str[i]));
}

ssize_t	get_immediate_operand(t_lst* symbol_table, t_token* token)
{
	t_lst*	label = (t_lst *)lst_find(symbol_table, token->str, cmp_label);
	if (label != NULL)
		return ((ssize_t)((t_label *)label->content)->line);
	else
		return (get_number(token->str));
}

ssize_t	get_condition_operand(t_isa* isa, t_token* token)
{
	size_t*	flag = (size_t *)get_assembling_target(isa, token->str, FLAG);
	if (flag != NULL)
		return ((ssize_t)*flag);
	else
		return (get_number(token->str));
}
