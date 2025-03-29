#pragma once

/* ----- INCLUDES ----- */

#include <stdbool.h>

/* ----- PROTOTYPES ----- */

// utils/
//	cmp.c
bool	cmp_label(void* label, void* str);
bool	cmp_macro(void* macro, void* str);
bool	cmp_token(void* token, void* str);
bool	cmp_flag(void* flag, void* ptr);
bool	cmp_register(void* _register, void* ptr);
