#pragma once

/* ----- INCLUDES ----- */

#include "file.h"
#include "isa.h"
#include "arguments.h"

/* ----- TYPES DECLARATIONS ----- */

typedef struct	lst	t_lst;

/* ----- STRUCTURES ----- */

// Generic data storage
typedef struct data
{
	t_option_parameter*	options;
	t_parr			files;
	t_lst*			tokens;
	t_lst*			macro_table;
	t_lst*			symbol_table;
	t_isa			isa;
}	t_data;
