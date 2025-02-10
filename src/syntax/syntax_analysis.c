#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "indulc.h"
#include "error.h"
#include "token.h"

static bool	check_remaining_tokens_syntax(t_lst** tokens_ptr)
{
	t_lst*	tokens = *tokens_ptr;
	while (tokens != NULL)
	{
		fprintf(stderr, "%s: %s (%zu:%zu): %s: \"%s\"\n", EXECUTABLE_NAME, ERROR_SYNTAX,
			((t_token *)tokens->content)->lin, ((t_token *)tokens->content)->col,
			ERROR_UNRECOGNIZED_TOKEN, ((t_token *)tokens->content)->str);
		tokens = tokens->next;
	}
	*tokens_ptr = tokens;
	return (1);
}

static bool	check_register_operand_syntax(t_isa* isa, t_token* token, t_bitfield* bitfield)
{
	size_t	i = 0;
	if (tolower(token->str[i]) == 'r')
		i++;
	if (is_number(&token->str[i]) == 0)
	{
		fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: \"%s\"\n", EXECUTABLE_NAME, ERROR_SYNTAX,
			token->lin, token->col, ERROR_INSTRUCTION, ERROR_NOT_NUMBER, token->str);
		return (1);
	}
	else if (will_overflow(&token->str[i], bitfield->len) == 1)
		fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: \"%s\"\n", EXECUTABLE_NAME, WARNING_SYNTAX,
			token->lin, token->col, WARNING_INSTRUCTION, WARNING_OVERFLOW, token->str);
	ssize_t	number = get_number(&token->str[i]);
	if (number < 0)
	{
		fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: \"%s\"\n", EXECUTABLE_NAME, ERROR_SYNTAX,
			token->lin, token->col, ERROR_INSTRUCTION, ERROR_NEGATIVE_NUMBER, token->str);
		return (1);
	}
	else if (number >= (ssize_t)isa->n_registers)
	{
		fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: \"%s\"\n", EXECUTABLE_NAME, ERROR_SYNTAX,
			token->lin, token->col, ERROR_INSTRUCTION, ERROR_INSTRUCTION_REGISTER,
			token->str);
		return (1);
	}
	return (0);
}

static bool	check_immediate_operand_syntax(t_lst* symbol_table, t_token* token, t_bitfield* bitfield)
{
	if (lst_find(symbol_table, token->str, cmp_label) != NULL)
		return (0);
	if (is_number(token->str) == 0)
	{
		fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: \"%s\"\n", EXECUTABLE_NAME, ERROR_SYNTAX,
			token->lin, token->col, ERROR_INSTRUCTION, ERROR_NOT_NUMBER, token->str);
		return (1);
	}
	else if (will_overflow(token->str, bitfield->len) == 1)
		fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: \"%s\"\n", EXECUTABLE_NAME, WARNING_SYNTAX,
			token->lin, token->col, WARNING_INSTRUCTION, WARNING_OVERFLOW, token->str);
	return (0);
}

static bool	check_condition_operand_syntax(t_isa* isa, t_token* token, t_bitfield* bitfield)
{
	t_flag*	flag = (t_flag *)get_compilation_target(isa, token->str, FLAG);
	if (flag != NULL)
		return (0);
	else if (is_number(token->str) == 0)
	{
		fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: \"%s\"\n", EXECUTABLE_NAME, ERROR_SYNTAX,
			token->lin, token->col, ERROR_INSTRUCTION, ERROR_NOT_NUMBER, token->str);
		return (1);
	}
	else if (will_overflow(token->str, bitfield->len) == 1)
		fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: \"%s\"\n", EXECUTABLE_NAME, WARNING_SYNTAX,
			token->lin, token->col, WARNING_INSTRUCTION, WARNING_OVERFLOW, token->str);
	ssize_t	number = get_number(token->str);
	if (number < 0)
	{
		fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: \"%s\"\n", EXECUTABLE_NAME, ERROR_SYNTAX,
			token->lin, token->col, ERROR_INSTRUCTION, ERROR_NEGATIVE_NUMBER, token->str);
		return (1);
	}
	else if (number >= (ssize_t)isa->n_flags)
	{
		fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: \"%s\"\n", EXECUTABLE_NAME, ERROR_SYNTAX,
			token->lin, token->col, ERROR_INSTRUCTION, ERROR_INSTRUCTION_FLAG,
			token->str);
		return (1);
	}
	return (0);
}

static bool	check_operand_syntax(t_data* data, t_instruction* instr, t_token* token, size_t i_opword)
{
	t_bitfield*	bitfield = get_bitfield(instr, i_opword);
	if (bitfield->type == REGISTER)
		return (check_register_operand_syntax(&data->isa, token, bitfield));
	else if (bitfield->type == IMMEDIATE)
		return (check_immediate_operand_syntax(data->symbol_table, token, bitfield));
	else if (bitfield->type == CONDITION)
		return (check_condition_operand_syntax(&data->isa, token, bitfield));
	return (0);
}

static bool	check_instruction_syntax(t_data* data, t_lst **tokens_ptr)
{
	t_lst*	tokens = *tokens_ptr;
	t_instruction*	instr = (t_instruction *)get_compilation_target(&data->isa,
		((t_token *)tokens->content)->str, INSTRUCTION);
	if (instr == NULL)
		return (0);
	bool	error = 0;
	size_t	i_opword = 0;
	while (tokens->next != NULL && i_opword + 1 < instr->n_opwords)
	{
		tokens = tokens->next;
		i_opword++;
		if (check_operand_syntax(data, instr, (t_token *)tokens->content, i_opword) == 1)
			error = 1;
	}
	*tokens_ptr = tokens->next;
	if (i_opword + 1 < instr->n_opwords)
	{
		fprintf(stderr, "%s: %s (%zu:%zu): %s: %s\n", EXECUTABLE_NAME, ERROR_SYNTAX,
			((t_token *)tokens->content)->lin, ((t_token *)tokens->content)->col
				+ strlen(((t_token *)tokens->content)->str) + 1,
			ERROR_INSTRUCTION, ERROR_INSTRUCTION_TOO_FEW_ARGS);
		return (1);
	}
	else if (tokens->next != NULL)
	{
		fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: \"%s\"\n", EXECUTABLE_NAME, ERROR_SYNTAX,
			((t_token *)tokens->next->content)->lin,
			((t_token *)tokens->next->content)->col, ERROR_INSTRUCTION,
			ERROR_INSTRUCTION_TOO_MANY_ARGS, ((t_token *)tokens->next->content)->str);
		return (1);
	}
	return (error);
}

static bool	check_label_syntax(t_lst **tokens_ptr)
{
	bool	error = 0;
	t_lst*	tokens = *tokens_ptr;
	ssize_t	i = lst_find_index(tokens, LABEL_KEYWORD, cmp_token);
	if (i == -1)
		return (0);
	*tokens_ptr = lst_get_node(tokens, i + 1);
	if (i < 1)
	{
		fprintf(stderr, "%s: %s (%zu:%zu): %s: %s\n", EXECUTABLE_NAME, ERROR_SYNTAX,
			((t_token *)tokens->content)->lin, ((t_token *)tokens->content)->col,
			ERROR_LABEL, ERROR_LABEL_TOO_FEW_ARGS);
		return (1);
	}
	else if (isalpha(((t_token *)tokens->content)->str[0]) == 0)
	{
		fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: \"%s\"\n", EXECUTABLE_NAME, ERROR_SYNTAX,
			((t_token *)tokens->content)->lin, ((t_token *)tokens->content)->col,
			ERROR_LABEL, ERROR_LABEL_INVALID_NAME, ((t_token *)tokens->content)->str);
		error = 1;
	}
	tokens = tokens->next;
	size_t	i_error = 1;
	while (i_error < (size_t)i)
	{
		fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: \"%s\"\n", EXECUTABLE_NAME, ERROR_SYNTAX,
			((t_token *)tokens->content)->lin, ((t_token *)tokens->content)->col,
			ERROR_LABEL, ERROR_LABEL_TOO_MANY_ARGS, ((t_token *)tokens->content)->str);
		error = 1;
		tokens = tokens->next;
		i_error++;
	}
	return (error);
}

static bool	check_define_syntax(t_lst **tokens_ptr)
{
	bool	error = 0;
	t_lst*	tokens = *tokens_ptr;
	if (strcmp(((t_token *)tokens->content)->str, DEFINE_KEYWORD) != 0)
		return (0);
	*tokens_ptr = lst_get_node(tokens, 3);
	if (tokens->next == NULL)
	{
		fprintf(stderr, "%s: %s (%zu:%zu): %s: %s\n", EXECUTABLE_NAME, ERROR_SYNTAX,
			((t_token *)tokens->content)->lin,
			((t_token *)tokens->content)->col
				+ strlen(((t_token *)tokens->content)->str) + 1,
			ERROR_DEFINE, ERROR_DEFINE_TOO_FEW_ARGS);
		return (1);
	}
	tokens = tokens->next;
	if (isalpha(((t_token *)tokens->content)->str[0]) == 0)
	{
		fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: \"%s\"\n", EXECUTABLE_NAME, ERROR_SYNTAX,
			((t_token *)tokens->content)->lin, ((t_token *)tokens->content)->col,
			ERROR_DEFINE, ERROR_DEFINE_INVALID_NAME, ((t_token *)tokens->content)->str);
		error = 1;
	}
	if (tokens->next == NULL)
	{
		fprintf(stderr, "%s: %s (%zu:%zu): %s: %s\n", EXECUTABLE_NAME, ERROR_SYNTAX,
			((t_token *)tokens->content)->lin,
			((t_token *)tokens->content)->col
				+ strlen(((t_token *)tokens->content)->str) + 1,
			ERROR_DEFINE, ERROR_DEFINE_TOO_FEW_ARGS);
		return (1);
	}
	tokens = tokens->next;
	if (is_number(((t_token *)tokens->content)->str) == 0)
	{
		fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: \"%s\"\n", EXECUTABLE_NAME, ERROR_SYNTAX,
			((t_token *)tokens->content)->lin, ((t_token *)tokens->content)->col,
			ERROR_DEFINE, ERROR_NOT_NUMBER, ((t_token *)tokens->content)->str);
		error = 1;
	}
	if (will_overflow(((t_token *)tokens->content)->str, 16) == 1)
		fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: \"%s\"\n", EXECUTABLE_NAME, WARNING_SYNTAX,
			((t_token *)tokens->content)->lin, ((t_token *)tokens->content)->col,
			WARNING_DEFINE, WARNING_OVERFLOW, ((t_token *)tokens->content)->str);
	tokens = tokens->next;
	if (tokens != NULL)
	{
		fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: \"%s\"\n", EXECUTABLE_NAME, ERROR_SYNTAX,
			((t_token *)tokens->content)->lin, ((t_token *)tokens->content)->col,
			ERROR_DEFINE, ERROR_DEFINE_TOO_MANY_ARGS, ((t_token *)tokens->content)->str);
		return (1);
	}
	return (error);
}

bool	syntax_analysis(t_data *data)
{
	bool	error = 0;
	t_lst*	tokens_lin = data->tokens;
	while (tokens_lin != NULL)
	{
		t_lst*	tokens_col = (t_lst *)tokens_lin->content;
		if (tokens_col != NULL && check_define_syntax(&tokens_col) == 1)
			error = 1;
		if (tokens_col != NULL && check_label_syntax(&tokens_col) == 1)
			error = 1;
		if (tokens_col != NULL && check_instruction_syntax(data, &tokens_col) == 1)
			error = 1;
		if (tokens_col != NULL && check_remaining_tokens_syntax(&tokens_col) == 1)
			error = 1;
		tokens_lin = tokens_lin->next;
	}
	return (error);
}
