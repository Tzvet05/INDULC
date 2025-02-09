#include "lst.h"

ssize_t	lst_find_index(t_lst* lst, void* to_find, bool (*cmp)(void*, void*))
{
	ssize_t	i = 0;
	while (lst != NULL)
	{
		if (cmp(lst->content, to_find) == 1)
			return (i);
		lst = lst->next;
		i++;
	}
	return (-1);
}
