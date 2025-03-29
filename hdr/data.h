#pragma once

/* ----- INCLUDES ----- */

#include "file.h"
#include "lst.h"
#include "isa.h"

/* ----- STRUCTURES ----- */

// Generic data storage
typedef struct data
{
	t_file	files[3];
	t_lst*	tokens;
	t_lst*	macro_table;
	t_lst*	symbol_table;
	t_isa	isa;
}	t_data;
