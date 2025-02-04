#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "indulc.h"
#include "error.h"
#include "token.h"
#include "macro.h"

static bool	is_define(t_lst* tokens)
{
	if (strcmp(((t_token *)tokens->content)->str, DEFINE_KEYWORD) != 0)
		return (0);
	else if (tokens->next == NULL)
		return (0);
	else if (isalpha(((t_token *)tokens->next->content)->str[0]) == 0)
		return (0);
	else if (tokens->next->next == NULL)
		return (0);
	else if (tokens->next->next->next != NULL)
		return (0);
	else
		return (1);
}

static bool	add_macro(t_lst* tokens, t_lst** macro_table)
{
	t_lst*	existing_macro = lst_find(*macro_table,
		((t_token *)tokens->next->content)->str, cmp_macro);
	if (existing_macro != NULL)
	{
		free(((t_macro *)existing_macro->content)->value);
		((t_macro *)existing_macro->content)->value =
			strdup(((t_token *)tokens->next->next->content)->str);
		if (((t_macro *)existing_macro->content)->value == NULL)
			return (1);
	}
	else
	{
		t_macro*	new_macro = malloc(sizeof(t_macro));
		if (new_macro == NULL)
			return (1);
		size_t	len_identifier = strlen(((t_token *)tokens->next->content)->str),
			len_value = strlen(((t_token *)tokens->next->next->content)->str);
		new_macro->identifier = malloc((len_identifier + 1) * sizeof(char));
		new_macro->value = malloc((len_value + 1) * sizeof(char));
		if (new_macro->identifier == NULL || new_macro->value == NULL)
		{
			free_macro(new_macro);
			return (1);
		}
		new_macro->identifier[len_identifier] = '\0';
		new_macro->value[len_value] = '\0';
		strcpy(new_macro->identifier, ((t_token *)tokens->next->content)->str);
		strcpy(new_macro->value, ((t_token *)tokens->next->next->content)->str);
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
		t_lst*	macro_target = (t_lst *)lst_find(macro_table,
			((t_token *)tokens->content)->str, cmp_macro);
		if (macro_target != NULL)
		{
			free(((t_token *)tokens->content)->str);
			((t_token *)tokens->content)->str
				= strdup(((t_macro *)macro_target->content)->value);
			if (((t_token *)tokens->content)->str == NULL)
				return (1);
		}
		tokens = tokens->next;
	}
	return (0);
}

bool	preprocessing(t_data* data)
{
	t_lst*	tokens = data->tokens;
	while (tokens != NULL)
	{
		bool	define = is_define((t_lst *)tokens->content);
		if (define == 1 && add_macro((t_lst *)tokens->content, &data->macro_table) == 1)
		{
			fprintf(stderr, "%s: %s: %s\n",
				EXECUTABLE_NAME, FUNC_MALLOC, ERROR_FAILED_ALLOC);
			return (1);
		}
		else if (define == 0
			&& substitute_macros(data->macro_table, (t_lst *)tokens->content))
		{
			fprintf(stderr, "%s: %s: %s\n",
				EXECUTABLE_NAME, FUNC_MALLOC, ERROR_FAILED_ALLOC);
			return (1);
		}
		tokens = tokens->next;
	}
	return (0);
}
