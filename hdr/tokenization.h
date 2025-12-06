#pragma once

/* ----- INCLUDES ----- */

#include <stdbool.h>
#include <stddef.h>

/* ----- TYPES DECLARATIONS ----- */

typedef struct	parr	t_parr;
typedef struct	lst	t_lst;
typedef struct	data	t_data;
typedef struct	keyword	t_keyword;

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
//	parse.c
t_keyword	*parse_keyword(const t_parr *keywords, char *line, size_t i_char);
//	free.c
void	free_token(void *token);
void	free_tokens(t_lst **token_col);
