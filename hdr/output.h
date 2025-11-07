#pragma once

/* ----- INCLUDES ----- */

#include "cJSON.h"
#include "parr.h"

/* ----- STRUCTURES ----- */

typedef struct	output
{
	t_parr	machine_code;
	cJSON	*json;
	t_parr	string;
}	t_output;
