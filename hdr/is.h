#pragma once

/* ----- INCLUDES ----- */

#include <stdbool.h>

/* ----- TYPES DECLARATIONS ----- */

typedef struct	isa	t_isa;
typedef struct	lst	t_lst;

/* ----- PROTOTYPES ----- */

// utils/
//	is.c
bool	is_option(char *str);
bool	has_parameter(char *str);
bool	is_define(t_lst *tokens);
bool	is_label(t_lst *tokens);
bool	has_instruction(t_isa *isa, t_lst *tokens);
