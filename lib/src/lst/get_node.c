#include <stddef.h>
#include "lst.h"

t_lst	*lst_get_node(t_lst *lst, size_t i)
{
	while (i > 0 && lst != NULL)
	{
		lst = lst->next;
		i--;
	}
	return (lst);
}
