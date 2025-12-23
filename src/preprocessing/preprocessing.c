#include <stdlib.h>
#include <string.h>
#include "lst.h"
#include "data.h"
#include "tokenization.h"
#include "preprocessing.h"
#include "cmp.h"
#include "is.h"
#include "error.h"

static bool	add_macro(lst_t *tokens, lst_t **macro_table)
{
	lst_t	*macro = lst_find(*macro_table, ((token_t *)tokens->next->content)->str, cmp_macro);
	if (macro != NULL)
	{
		if (((macro_t *)macro->content)->n_uses == 0)
			fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: \"%s\"\n",
				EXECUTABLE_NAME, WARNING_SYNTAX,
				((macro_t *)macro->content)->identifier->lin,
				((macro_t *)macro->content)->identifier->col, WARNING_DEFINE,
				WARNING_DEFINE_UNUSED, ((token_t *)tokens->next->content)->str);
		((macro_t *)macro->content)->identifier = tokens->next->content;
		((macro_t *)macro->content)->substitute = tokens->next->next->content;
		((macro_t *)macro->content)->n_uses = 0;
	}
	else if (strcmp(((token_t *)tokens->next->content)->str,
		((token_t *)tokens->next->next->content)->str) != 0)
	{
		macro_t	*new_macro = malloc(sizeof(macro_t));
		if (new_macro == NULL)
			return (1);
		new_macro->identifier = tokens->next->content;
		new_macro->substitute = tokens->next->next->content;
		new_macro->n_uses = 0;
		if (lst_new_back(macro_table, new_macro) == 1)
		{
			free_macro(new_macro);
			return (1);
		}
	}
	return (0);
}

static bool	substitute_macros(lst_t *macro_table, lst_t *tokens)
{
	while (tokens != NULL)
	{
		lst_t	*macro = lst_find(macro_table, ((token_t *)tokens->content)->str,
			cmp_macro);
		if (macro != NULL)
		{
			free(((token_t *)tokens->content)->str);
			((token_t *)tokens->content)->str
				= strdup(((macro_t *)macro->content)->substitute->str);
			if (((token_t *)tokens->content)->str == NULL)
				return (1);
			((macro_t *)macro->content)->n_uses++;
		}
		tokens = tokens->next;
	}
	return (0);
}

bool	preprocess(data_t *data)
{
	lst_t	*tokens = data->tokens;
	while (tokens != NULL)
	{
		if (is_define(tokens->content) == 1)
		{
			if (add_macro(tokens->content, &data->macro_table) == 1)
			{
				fprintf(stderr, "%s: %s: %s: %s: %s\n",
					EXECUTABLE_NAME, ERROR_FUNCTION, LIB_LIBC, FUNC_MALLOC,
					ERROR_ALLOC);
				return (1);
			}
		}
		else if (substitute_macros(data->macro_table, tokens->content) == 1)
		{
			fprintf(stderr, "%s: %s: %s: %s: %s\n",
				EXECUTABLE_NAME, ERROR_FUNCTION, LIB_LIBC, FUNC_MALLOC,
				ERROR_ALLOC);
			return (1);
		}
		tokens = tokens->next;
	}
	check_macros(data->macro_table);
	return (0);
}
