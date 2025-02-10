#pragma once

/* ----- INCLUDES ----- */

#include <stddef.h>
#include "token.h"

/* ----- STRUCTURES ----- */

// Label
typedef struct label
{
	t_token*	name;
	size_t		line;
}	t_label;
