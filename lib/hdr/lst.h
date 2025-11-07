#pragma once

/* ----- INCLUDES ----- */

#include <stdbool.h>
#include <sys/types.h>

/* ----- STRUCTURES ----- */

// Linked list
typedef struct lst
{
	void		*content;
	struct lst	*next;
}	t_lst;

/* ----- PROTOTYPES ----- */

// lst/
//	last.c
t_lst	*lst_last(t_lst *lst);
//	new_back.c
bool	lst_new_back(t_lst **lst, void *content);
//	clear.c
void	lst_clear(t_lst **lst, void (*del)(void*));
//	find_index.c
ssize_t	lst_find_index(t_lst *lst, void *to_find, bool (*cmp)(void*, void*));
//	get_node.c
t_lst	*lst_get_node(t_lst *lst, size_t i);
//	find.c
t_lst	*lst_find(t_lst *lst, void *to_find, bool (*cmp)(void*, void*));
