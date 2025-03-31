#include <stdlib.h>
#include "lst.h"

void	lst_clear(t_lst** lst, void (*del)(void*))
{
	t_lst*	current = *lst, *next;
	*lst = NULL;
	while (current != NULL)
	{
		next = current->next;
		if (del != NULL)
			del(current->content);
		free(current);
		current = next;
	}
}
