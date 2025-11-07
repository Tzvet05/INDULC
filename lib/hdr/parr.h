#pragma once

/* ----- INCLUDES ----- */

#include <stdbool.h>
#include <stddef.h>

/* ----- STRUCTURES ----- */

// Pascal-style-string-like array
typedef struct parr
{
	void	*arr;
	size_t	obj_size;
	size_t	len;
}	t_parr;

/* ----- PROTOTYPES ----- */

// parr/
//	find.c
void	*parr_find(t_parr *parr, void *to_find, bool (*cmp)(void*, void*));
//	clear.c
void	parr_clear(t_parr *parr, void (*del)(void*));
