#include <stddef.h>
#include "lst.h"

lst_t	*lst_find(lst_t *lst, void *to_find, bool (*cmp)(void*, void*))
{
	while (lst != NULL)
	{
		if (cmp(lst->content, to_find) == 0)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}
