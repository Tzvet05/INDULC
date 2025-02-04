#include "lst.h"

size_t	lst_size(t_lst* lst)
{
	size_t	len = 0;

	while (lst != NULL)
	{
		lst = lst->next;
		len++;
	}
	return (len);
}
