#pragma once

/* ----- INCLUDES ----- */

#include "isa.h"

/* ----- PROTOTYPES ----- */

// utils/
//	assembling.c
t_instruction*	get_instruction(t_isa* isa, char* instruction);
t_flag*		get_flag(t_isa* isa, char* flag);
t_register*	get_register(t_isa* isa, char* _register);
