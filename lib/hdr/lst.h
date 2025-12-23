#pragma once

/* ----- INCLUDES ----- */

#include <stdbool.h>
#include <sys/types.h>

/* ----- STRUCTURES ----- */

// Linked list
typedef struct	lst
{
	void		*content;
	struct lst	*next;
}	lst_t;

/* ----- PROTOTYPES ----- */

// lst/
//	last.c
lst_t	*lst_last(lst_t *lst);
//	new_back.c
bool	lst_new_back(lst_t **lst, void *content);
//	clear.c
void	lst_clear(lst_t **lst, void (*del)(void*));
//	find_index.c
ssize_t	lst_find_index(lst_t *lst, void *to_find, bool (*cmp)(void*, void*));
//	get_node.c
lst_t	*lst_get_node(lst_t *lst, size_t i);
//	find.c
lst_t	*lst_find(lst_t *lst, void *to_find, bool (*cmp)(void*, void*));
