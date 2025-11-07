#pragma once

/* ----- INCLUDES ----- */

#include <stdbool.h>
#include "cJSON.h"
#include "arguments.h"

/* ----- TYPES DECLARATIONS ----- */

typedef struct	file	t_file;

/* ----- PROTOTYPES ----- */

// output_writing/
//	outputs.c
bool	write_machine_code(t_parr *output, t_file *file, t_option_parameter *options);
bool	write_json(cJSON *json, t_file *file, t_option_parameter *options);
bool	write_string(t_parr *string, t_file *file, t_option_parameter *options);
