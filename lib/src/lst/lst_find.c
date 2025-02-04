#include "lst.h"

t_lst*	lst_find(t_lst* lst, void* to_find, bool (*cmp)(void*, void*))
{
	while (lst != NULL)
	{
		if (cmp(lst->content, to_find) == 1)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}
