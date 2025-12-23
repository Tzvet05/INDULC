#pragma once

/* ----- INCLUDES ----- */

#include <sys/types.h>
#include <stdbool.h>

/* ----- TYPES DECLARATIONS ----- */

typedef struct	data	data_t;
typedef struct	isa	isa_t;
typedef struct	lst	lst_t;
typedef struct	token	token_t;

/* ----- PROTOTYPES ----- */

// machine_code/
//	generation.c
bool	generate_machine_code(data_t *data);
//	get_operand.c
ssize_t	get_register_operand(isa_t *isa, token_t *token);
ssize_t	get_immediate_operand(lst_t *symbol_table, token_t *token);
ssize_t	get_condition_operand(isa_t *isa, token_t *token);
//	utils.c
size_t	count_instructions(isa_t *isa, lst_t *tokens);
