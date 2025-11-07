#pragma once

/* ----- INCLUDES ----- */

#include <stdbool.h>
#include <stddef.h>

/* ----- TYPES DECLARATIONS ----- */

typedef struct	lst	t_lst;
typedef struct	data	t_data;

/* ----- STRUCTURES ----- */

typedef struct	token
{
	char	*str;
	size_t	lin;
	size_t	col;
}	t_token;

/* ----- PROTOTYPES ----- */

// tokenization/
//	tokenization.c
bool	tokenize(t_data *data);
//	free.c
void	free_tokens(t_lst **token_col);
