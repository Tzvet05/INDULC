#pragma once

/* ----- INCLUDES ----- */

#include "isa.h"
#include "token.h"
#include "lst.h"

/* ----- PROTOTYPES ----- */

// machine_code/
//	machine_code_generation.c
bool	generate_machine_code(t_data* data);
//	get_operand.c
ssize_t	get_register_operand(t_isa* isa, t_token* token);
ssize_t	get_immediate_operand(t_lst* symbol_table, t_token* token);
ssize_t	get_condition_operand(t_isa* isa, t_token* token);
