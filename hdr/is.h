#pragma once

/* ----- INCLUDES ----- */

#include <stdbool.h>

/* ----- TYPES DECLARATIONS ----- */

typedef struct	isa	isa_t;
typedef struct	lst	lst_t;

/* ----- PROTOTYPES ----- */

// utils/
//	is.c
bool	is_option(char *str);
bool	has_parameter(char *str);
bool	is_define(lst_t *tokens);
bool	is_label(lst_t *tokens);
bool	has_instruction(isa_t *isa, lst_t *tokens);
