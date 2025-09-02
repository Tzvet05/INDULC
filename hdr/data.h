#pragma once

/* ----- INCLUDES ----- */

#include <stdint.h>
#include "lst.h"
#include "file.h"
#include "isa.h"

/* ----- STRUCTURES ----- */

// Generic data storage
typedef struct data
{
	t_file	files[3];
	uint8_t	options;
	t_lst*	tokens;
	t_lst*	macro_table;
	t_lst*	symbol_table;
	t_isa	isa;
}	t_data;
