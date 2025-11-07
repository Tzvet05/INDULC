#include <stdlib.h>
#include "lst.h"

bool	lst_new_back(t_lst **lst, void *content)
{
	t_lst	*new = malloc(sizeof(t_lst));
	if (new == NULL)
		return (1);
	new->content = content;
	new->next = NULL;
	while (*lst != NULL)
		lst = &(*lst)->next;
	*lst = new;
	return (0);
}
