#pragma once

/* ----- INCLUDES ----- */

#include <stdbool.h>
#include "tokenization.h"

/* ----- TYPES DECLARATIONS ----- */

typedef struct	lst	t_lst;
typedef struct	data	t_data;
typedef struct	isa	t_isa;

/* ----- STRUCTURES ----- */

// Label
typedef struct label
{
	t_token*	name;
	size_t		line;
}	t_label;

/* ----- PROTOTYPES ----- */

// symbol_table/
//	symbol_table_building.c
bool	build_symbol_table(t_data* data);
//	symbol_table_utils.c
bool	is_label(t_lst* tokens);
bool	has_instruction(t_isa* isa, t_lst* tokens);
//	free_label.c
void	free_label(void* label);
