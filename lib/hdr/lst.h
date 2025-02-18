#pragma once

/* ----- INCLUDES ----- */

// Libraries
#include <stdlib.h>
#include <stdbool.h>

// Headers
#include "parr.h"

/* ----- STRUCTURES ----- */

// Linked list
typedef struct lst
{
	void*		content;
	struct lst*	next;
}	t_lst;

/* ----- PROTOTYPES ----- */

// Linked list
size_t	lst_size(t_lst* lst);
t_lst*	lst_last(t_lst* lst);
bool	lst_new_back(t_lst** lst, void* content);
void	lst_clear(t_lst** lst, void (*del)(void*));
ssize_t	lst_find_index(t_lst* lst, void* to_find, bool (*cmp)(void*, void*));
t_lst*	lst_get_node(t_lst* lst, size_t i);
t_lst*	lst_find(t_lst* lst, void* to_find, bool (*cmp)(void*, void*));
bool	lst_to_parr(t_lst* lst, t_parr** parr);
