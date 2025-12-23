#include <stdlib.h>
#include "lst.h"

void	lst_clear(lst_t **lst, void (*del)(void*))
{
	lst_t	*current = *lst;
	*lst = NULL;
	while (current != NULL)
	{
		lst_t	*next = current->next;
		if (del != NULL)
			del(current->content);
		free(current);
		current = next;
	}
}
