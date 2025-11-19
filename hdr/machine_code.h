#pragma once

/* ----- INCLUDES ----- */

#include <sys/types.h>
#include <stdbool.h>

/* ----- TYPES DECLARATIONS ----- */

typedef struct	data	t_data;
typedef struct	isa	t_isa;
typedef struct	lst	t_lst;
typedef struct	token	t_token;

/* ----- PROTOTYPES ----- */

// machine_code/
//	generation.c
bool	generate_machine_code(t_data *data);
//	get_operand.c
ssize_t	get_register_operand(t_isa *isa, t_token *token);
ssize_t	get_immediate_operand(t_lst *symbol_table, t_token *token);
ssize_t	get_condition_operand(t_isa *isa, t_token *token);
//	utils.c
size_t	count_instructions(t_isa *isa, t_lst *tokens);
