#pragma once

/* ----- INCLUDES ----- */

#include "token.h"
#include "lst.h"

/* ----- STRUCTURES ----- */

// Macro
typedef struct macro
{
	t_token*	identifier;
	t_token*	substitute;
}	t_macro;

/* ----- PROTOTYPES ----- */

// preprocessing/
//	preprocessing_utils.c
bool	is_define(t_lst* tokens);
//	free_macro.c
void	free_macro(void* macro);
