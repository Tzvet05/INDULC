#pragma once

/* ----- INCLUDES ----- */

#include "lst.h"

/* ----- STRUCTURES ----- */

typedef struct token
{
	char*	str;
	size_t	lin;
	size_t	col;
}	t_token;

/* ----- PROTOTYPES ----- */

// tokenization/
//	free_tokens.c
void	free_tokens(t_lst* token_col);
void	free_token(void* token);
