#pragma once

/* ----- INCLUDES ----- */

#include "cJSON.h"

/* ----- TYPES DECLARATIONS ----- */

typedef struct	file	file_t;

/* ----- PROTOTYPES ----- */

const cJSON	*parse_json_file(file_t *file);
