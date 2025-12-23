#pragma once

/* ----- INCLUDES ----- */

#include <stdbool.h>
#include <stddef.h>

/* ----- TYPES DECLARATIONS ----- */

typedef struct	data	data_t;
typedef struct	token	token_t;
typedef struct	lst	lst_t;

/* ----- STRUCTURES ----- */

// Macro
typedef struct	macro
{
	token_t	*identifier;
	token_t	*substitute;
	size_t	n_uses;
}	macro_t;

/* ----- PROTOTYPES ----- */

// preprocessing/
//	preprocessing.c
bool	preprocess(data_t *data);
//	check.c
void	check_macros(lst_t *macro_table);
//	free.c
void	free_macro(void *macro);
