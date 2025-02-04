#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "indulc.h"
#include "token.h"
#include "label.h"
#include "error.h"

bool	is_label(t_lst* tokens)
{
	if (tokens->next == NULL)
		return (0);
	else if (strcmp(((t_token *)tokens->next->content)->str, LABEL_KEYWORD) != 0)
		return (0);
	else if (isalpha(((t_token *)tokens->content)->str[0]) == 0)
		return (0);
	else
		return (1);
}

static bool	add_label(t_lst* tokens, t_lst** symbol_table, size_t line)
{
	t_lst*	existing_label = lst_find(*symbol_table,
		((t_token *)tokens->content)->str, cmp_label);
	if (existing_label != NULL)
	{
		fprintf(stderr, "%s: %s (%zu:%zu): %s: \"%s\"\n",
			EXECUTABLE_NAME, ERROR_SYNTAX, ((t_token *)tokens->content)->lin,
			((t_token *)tokens->content)->col, ERROR_LABEL_DUPLICATE,
			((t_token *)tokens->content)->str);
		return (1);
	}
	else
	{
		t_label*	label = malloc(sizeof(t_label));
		if (label == NULL)
			return (1);
		size_t	len_name = strlen(((t_token *)tokens->content)->str);
		label->name = malloc((len_name + 1) * sizeof(char));
		if (label->name == NULL)
		{
			free_label(label);
			return (1);
		}
		label->name[len_name] = '\0';
		strcpy(label->name, ((t_token *)tokens->content)->str);
		if (tokens->next->next == NULL)
			label->line = line + 1;
		else
			label->line = line;
		if (lst_new_back(symbol_table, label) == 1)
		{
			free_label(label);
			return (1);
		}
	}
	return (0);
}

static bool	has_instruction(t_isa* isa, t_lst* tokens)
{
	if (is_label(tokens) == 1)
		tokens = tokens->next->next;
	return (tokens != NULL && get_compilation_target(isa, ((t_token *)tokens->content)->str,
		INSTRUCTION) != NULL);
}

bool	symbol_table_building(t_data* data)
{
	size_t	line = 0;
	t_lst*	tokens = data->tokens;
	while (tokens != NULL)
	{
		if (is_label((t_lst *)tokens->content) == 1
			&& add_label((t_lst *)tokens->content, &data->symbol_table, line) == 1)
			return (1);
		if (has_instruction(&data->isa, (t_lst *)tokens->content) == 1)
			line++;
		tokens = tokens->next;
	}
	return (0);
}
