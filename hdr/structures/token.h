#pragma once

/* ----- INCLUDES ----- */

#include <stddef.h>

/* ----- STRUCTURES ----- */

typedef struct token
{
	char*	str;
	size_t	lin;
	size_t	col;
}	t_token;
