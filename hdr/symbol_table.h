#pragma once

/* ----- INCLUDES ----- */

#include <stdbool.h>
#include <stddef.h>

/* ----- TYPES DECLARATIONS ----- */

typedef struct	data	t_data;
typedef struct	token	t_token;

/* ----- STRUCTURES ----- */

// Label
typedef struct	label
{
	t_token	*name;
	size_t	line;
}	t_label;

/* ----- PROTOTYPES ----- */

// symbol_table/
//	building.c
bool	build_symbol_table(t_data *data);
//	free.c
void	free_label(void *label);
