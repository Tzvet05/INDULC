#pragma once

/* ----- INCLUDES ----- */

#include <stddef.h>

/* ----- STRUCTURES ----- */

// Pascal-style string
typedef struct	pstr
{
	size_t	len;
	char	*str;
}	t_pstr;
