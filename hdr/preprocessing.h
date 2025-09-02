#pragma once

/* ----- INCLUDES ----- */

#include "lst.h"
#include "data.h"
#include "macro.h"

// preprocessing/
//	preprocessing.c
bool	preprocess(t_data* data);
//	preprocessing_utils.c
bool	is_define(t_lst* tokens);
//	free_macro.c
void	free_macro(void* macro);
