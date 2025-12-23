#pragma once

/* ----- INCLUDES ----- */

#include <stdbool.h>
#include "cJSON.h"
#include "arguments.h"

/* ----- TYPES DECLARATIONS ----- */

typedef struct	file	file_t;

/* ----- PROTOTYPES ----- */

// output_writing/
//	outputs.c
bool	write_machine_code(parr_t *output, file_t *file, option_parameter_t *options);
bool	write_json(cJSON *json, file_t *file, option_parameter_t *options);
bool	write_string(parr_t *string, file_t *file, option_parameter_t *options);
