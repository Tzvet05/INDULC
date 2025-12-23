#include <stddef.h>
#include "lst.h"

lst_t	*lst_get_node(lst_t *lst, size_t i)
{
	while (i > 0 && lst != NULL)
	{
		lst = lst->next;
		i--;
	}
	return (lst);
}
