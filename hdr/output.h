#pragma once

/* ----- INCLUDES ----- */

#include "cJSON.h"
#include "parr.h"

/* ----- STRUCTURES ----- */

typedef struct	output
{
	parr_t	machine_code;
	cJSON	*json;
	parr_t	string;
}	output_t;
