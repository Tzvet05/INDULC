#pragma once

/* ----- INCLUDES ----- */

#include "cJSON.h"

/* ----- TYPES DECLARATIONS ----- */

typedef struct	file	t_file;

/* ----- PROTOTYPES ----- */

const cJSON	*parse_json_file(t_file *file);
