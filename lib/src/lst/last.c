#include <stddef.h>
#include "lst.h"

t_lst	*lst_last(t_lst *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
