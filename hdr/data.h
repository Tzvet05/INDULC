#pragma once

/* ----- INCLUDES ----- */

#include "isa.h"
#include "arguments.h"
#include "signals.h"
#include "output.h"

/* ----- TYPES DECLARATIONS ----- */

typedef struct	lst	lst_t;

/* ----- STRUCTURES ----- */

// Generic data storage
typedef struct	data
{
	option_parameter_t	*options;
	parr_t			files;
	lst_t			*tokens;
	lst_t			*macro_table;
	lst_t			*symbol_table;
	isa_t			isa;
	blueprint_t		blueprint;
	output_t		output;
}	data_t;
