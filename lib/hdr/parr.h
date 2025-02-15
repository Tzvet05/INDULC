#pragma once

/* ----- INCLUDES ----- */

// Libraries
#include <stddef.h>
#include <stdbool.h>

/* ----- STRUCTURES ----- */

// Pascal-type array
typedef struct parr
{
	void*	arr;
	size_t	len;
}	t_parr;

/* ----- PROTOTYPES ----- */

// Pascal-type array
void*	parr_find(t_parr* parr, void* to_find, bool (*cmp)(void*, void*), size_t size);
