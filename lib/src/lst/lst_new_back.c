#include "lst.h"

bool	lst_new_back(t_lst** lst, void* content)
{
	t_lst*	new = malloc(sizeof(t_lst));
	if (new == NULL)
		return (1);
	new->content = content;
	new->next = NULL;
	if (*lst == NULL)
		*lst = new;
	else
		lst_last(*lst)->next = new;
	return (0);
}
