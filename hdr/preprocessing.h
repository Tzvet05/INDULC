#pragma once

/* ----- INCLUDES ----- */

#include <stdbool.h>

/* ----- TYPES DECLARATIONS ----- */

typedef struct	data	t_data;
typedef struct	token	t_token;

/* ----- STRUCTURES ----- */

// Macro
typedef struct	macro
{
	t_token	*identifier;
	t_token	*substitute;
}	t_macro;

/* ----- PROTOTYPES ----- */

// preprocessing/
//	preprocessing.c
bool	preprocess(t_data *data);
//	free.c
void	free_macro(void *macro);
