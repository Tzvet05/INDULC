#pragma once

/* ----- INCLUDES ----- */

#include "token.h"

/* ----- STRUCTURES ----- */

// Macro
typedef struct macro
{
	t_token*	identifier;
	t_token*	substitute;
}	t_macro;
