#include <stddef.h>
#include "lst.h"

lst_t	*lst_last(lst_t *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
