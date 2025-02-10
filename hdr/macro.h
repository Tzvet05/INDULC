#pragma once

/* ----- INCLUDES ----- */

#include "token.h"

/* ----- STRUCTURES ----- */

// Macro
typedef struct macro
{
	t_token*	identifier;
	char*		value;
}	t_macro;
