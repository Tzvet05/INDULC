#pragma once

/* ----- INCLUDES ----- */

#include <stdbool.h>
#include <stddef.h>

/* ----- STRUCTURES ----- */

// Pascal-style-string-like array
typedef struct	parr
{
	size_t	len;
	size_t	obj_size;
	void	*arr;
}	parr_t;

/* ----- PROTOTYPES ----- */

// parr/
//	find.c
void	*parr_find(parr_t *parr, void *to_find, bool (*cmp)(void*, void*));
//	clear.c
void	parr_clear(parr_t *parr, void (*del)(void*));
