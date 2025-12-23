#pragma once

/* ----- INCLUDES ----- */

#include <stdbool.h>
#include <stddef.h>

/* ----- TYPES DECLARATIONS ----- */

typedef struct	data	data_t;
typedef struct	token	token_t;

/* ----- STRUCTURES ----- */

// Label
typedef struct	label
{
	token_t	*name;
	size_t	line;
	size_t	n_uses;
}	label_t;

/* ----- PROTOTYPES ----- */

// symbol_table/
//	building.c
bool	build_symbol_table(data_t *data);
//	check.c
bool	check_label(lst_t *tokens, lst_t *symbol_table);
void	check_labels(data_t *data);
//	free.c
void	free_label(void *label);
