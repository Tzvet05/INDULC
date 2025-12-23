#include <stdlib.h>
#include "lst.h"

bool	lst_new_back(lst_t **lst, void *content)
{
	lst_t	*new = malloc(sizeof(lst_t));
	if (new == NULL)
		return (1);
	new->content = content;
	new->next = NULL;
	while (*lst != NULL)
		lst = &(*lst)->next;
	*lst = new;
	return (0);
}
