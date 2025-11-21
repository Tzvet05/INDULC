#pragma once

/* ----- INCLUDES ----- */

#include <stdbool.h>
#include <stddef.h>

/* ----- TYPES DECLARATIONS ----- */

typedef struct	data	t_data;
typedef struct	token	t_token;
typedef struct	lst	t_lst;

/* ----- STRUCTURES ----- */

// Macro
typedef struct	macro
{
	t_token	*identifier;
	t_token	*substitute;
	size_t	n_uses;
}	t_macro;

/* ----- PROTOTYPES ----- */

// preprocessing/
//	preprocessing.c
bool	preprocess(t_data *data);
//	check.c
void	check_macros(t_lst *macro_table);
//	free.c
void	free_macro(void *macro);
