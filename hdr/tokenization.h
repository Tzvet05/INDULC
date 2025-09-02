#pragma once

/* ----- INCLUDES ----- */

#include <stdbool.h>
#include "lst.h"
#include "data.h"
#include "token.h"

/* ----- PROTOTYPES ----- */

// tokenization/
//	tokenization.c
bool	tokenize(t_data* data);
//	free_tokens.c
void	free_tokens(t_lst* token_col);
void	free_token(void* token);
