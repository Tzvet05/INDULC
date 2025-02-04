#pragma once

/* ----- INCLUDES ----- */

#include <stddef.h>

/* ----- STRUCTURES ----- */

// Pascal-type array
typedef struct parr
{
	void*	arr;
	size_t	len;
}	t_parr;
