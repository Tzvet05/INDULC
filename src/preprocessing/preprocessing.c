#include <string.h>
#include "data.h"
#include "error.h"
#include "macro.h"
#include "cmp.h"

static bool	add_macro(t_lst* tokens, t_lst** macro_table)
{
	t_lst*	macro = lst_find(*macro_table, ((t_token *)tokens->next->content)->str, cmp_macro);
	if (macro != NULL)
	{
		((t_macro *)macro->content)->identifier = (t_token *)tokens->next->content;
		((t_macro *)macro->content)->substitute = (t_token *)tokens->next->next->content;
	}
	else if (strcmp(((t_token *)tokens->next->content)->str,
		((t_token *)tokens->next->next->content)->str) != 0)
	{
		t_macro*	new_macro = malloc(sizeof(t_macro));
		if (new_macro == NULL)
			return (1);
		new_macro->identifier = (t_token *)tokens->next->content;
		new_macro->substitute = (t_token *)tokens->next->next->content;
		if (lst_new_back(macro_table, new_macro) == 1)
		{
			free_macro(new_macro);
			return (1);
		}
	}
	return (0);
}

static bool	substitute_macros(t_lst* macro_table, t_lst* tokens)
{
	while (tokens != NULL)
	{
		t_lst*	macro = (t_lst *)lst_find(macro_table,
			((t_token *)tokens->content)->str, cmp_macro);
		if (macro != NULL)
		{
			free(((t_token *)tokens->content)->str);
			((t_token *)tokens->content)->str
				= strdup(((t_macro *)macro->content)->substitute->str);
			if (((t_token *)tokens->content)->str == NULL)
				return (1);
		}
		tokens = tokens->next;
	}
	return (0);
}

bool	preprocess(t_data* data)
{
	t_lst*	tokens = data->tokens;
	while (tokens != NULL)
	{
		if (is_define((t_lst *)tokens->content) == 1)
		{
			if (add_macro((t_lst *)tokens->content, &data->macro_table) == 1)
			{
				fprintf(stderr, "%s: %s: %s\n",
					EXECUTABLE_NAME, FUNC_MALLOC, ERROR_FAILED_ALLOC);
				return (1);
			}
		}
		else if (substitute_macros(data->macro_table, (t_lst *)tokens->content) == 1)
		{
			fprintf(stderr, "%s: %s: %s\n",
				EXECUTABLE_NAME, FUNC_MALLOC, ERROR_FAILED_ALLOC);
			return (1);
		}
		tokens = tokens->next;
	}
	return (0);
}
