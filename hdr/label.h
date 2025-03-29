#pragma once

/* ----- INCLUDES ----- */

#include "token.h"
#include "isa.h"
#include "lst.h"

/* ----- STRUCTURES ----- */

// Label
typedef struct label
{
	t_token*	name;
	size_t		line;
}	t_label;

/* ----- PROTOTYPES ----- */

// symbol_table/
//	symbol_table_utils.c
bool	is_label(t_lst* tokens);
bool	has_instruction(t_isa* isa, t_lst* tokens);
//	free_label.c
void	free_label(void* label);
