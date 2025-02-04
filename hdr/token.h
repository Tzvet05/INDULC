#pragma once

/* ----- INCLUDES ----- */

#include <stddef.h>
#include "pstr.h"

/* ----- STRUCTURES ----- */

typedef struct token
{
	char*	str;
	size_t	lin;
	size_t	col;
}	t_token;
