#pragma once

/* ----- INCLUDES ----- */

#include <stdbool.h>
#include "isa.h"
#include "lst.h"
#include "data.h"
#include "label.h"

/* ----- PROTOTYPES ----- */

// symbol_table/
//	symbol_table_building.c
bool	build_symbol_table(t_data* data);
//	symbol_table_utils.c
bool	is_label(t_lst* tokens);
bool	has_instruction(t_isa* isa, t_lst* tokens);
//	free_label.c
void	free_label(void* label);
