#pragma once

/* ----- INCLUDES ----- */

#include <stdbool.h>
#include <stddef.h>

/* ----- TYPES DECLARATIONS ----- */

typedef struct	parr	parr_t;
typedef struct	lst	lst_t;
typedef struct	data	data_t;
typedef struct	keyword	keyword_t;

/* ----- STRUCTURES ----- */

typedef struct	token
{
	char	*str;
	size_t	lin;
	size_t	col;
}	token_t;

/* ----- PROTOTYPES ----- */

// tokenization/
//	tokenization.c
bool	tokenize(data_t *data);
//	parse.c
keyword_t	*parse_keyword(const parr_t *keywords, char *line, size_t i_char);
//	free.c
void	free_token(void *token);
void	free_tokens(lst_t **token_col);
