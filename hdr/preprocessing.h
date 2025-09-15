#pragma once

/* ----- INCLUDES ----- */

#include "tokenization.h"

/* ----- TYPES DECLARATIONS ----- */

typedef struct	lst	t_lst;
typedef struct	data	t_data;

/* ----- STRUCTURES ----- */

// Macro
typedef struct macro
{
	t_token*	identifier;
	t_token*	substitute;
}	t_macro;

/* ----- PROTOTYPES ----- */

// preprocessing/
//	preprocessing.c
bool	preprocess(t_data* data);
//	preprocessing_utils.c
bool	is_define(t_lst* tokens);
//	free_macro.c
void	free_macro(void* macro);
