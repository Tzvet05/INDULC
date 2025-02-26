#pragma once

/* ----- INCLUDES ----- */

#include <stddef.h>
#include <stdbool.h>

/* ----- STRUCTURES ----- */

// Pascal-style-string-like array
typedef struct parr
{
	void*	arr;
	size_t	obj_size;
	size_t	len;
}	t_parr;

/* ----- PROTOTYPES ----- */

void*	parr_find(t_parr* parr, void* to_find, bool (*cmp)(void*, void*));
