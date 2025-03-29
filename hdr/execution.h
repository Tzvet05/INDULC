#pragma once

/* ----- INCLUDES ----- */

#include "data.h"

/* ----- PROTOTYPES ----- */

// arguments/
//	argument_checking.c
bool	check_arguments(int n_files);

// isa/
//	isa_loading.c
bool	load_isa(t_data* data);

// tokenization/
//	tokenization.c
bool	tokenize(t_data* data);

// preprocessing/
//	preprocessing.c
bool	preprocess(t_data* data);

// symbol_table/
//	symbol_table_building.c
bool	build_symbol_table(t_data* data);

// syntax/
//	syntax_analysis.c
bool	analyse_syntax(t_data* data);

// machine_code/
//	machine_code_generation.c
bool	generate_machine_code(t_data* data);
