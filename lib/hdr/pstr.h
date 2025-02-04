#pragma once

/* ----- INCLUDES ----- */

#include <stddef.h>

/* ----- STRUCTURES ----- */

// Pascal-type string
typedef struct pstr
{
	char*	str;
	size_t	len;
}	t_pstr;
