#include <string.h>
#include <ctype.h>
#include "indulc.h"
#include "label.h"
#include "nbr.h"
#include "error.h"
#include <stdio.h>
static bool	check_register_operand_syntax(t_isa* isa, t_token* token, size_t bit_len)
{
	size_t	i = 0;
#ifdef COMP_STRICT_SYNTAX
	if (tolower(token->str[i]) != 'r')
	{
		fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: %s: \"%s\"\n",
			EXECUTABLE_NAME, ERROR_SYNTAX, token->lin, token->col,
			ERROR_INSTRUCTION, ERROR_INSTRUCTION_REGISTER,
			ERROR_INSTRUCTION_REGISTER_PREFIX, token->str);
		return (1);
	}
	i++;
#else
	if (tolower(token->str[i]) == 'r')
		i++;
#endif
	if (is_number(&token->str[i]) == 0)
	{
		fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: %s: \"%s\"\n",
			EXECUTABLE_NAME, ERROR_SYNTAX, token->lin, token->col,
			ERROR_INSTRUCTION, ERROR_INSTRUCTION_REGISTER,
			ERROR_NOT_NUMBER, token->str);
		return (1);
	}
	ssize_t	number = get_number(&token->str[i]);
	if (parr_find(&isa->registers, &number, cmp_register) == NULL)
	{
		fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: %s: \"%s\"\n",
			EXECUTABLE_NAME, ERROR_SYNTAX, token->lin, token->col,
			ERROR_INSTRUCTION, ERROR_INSTRUCTION_REGISTER,
			ERROR_INSTRUCTION_REGISTER_INDEX, token->str);
		return (1);
	}
	else if (will_overflow_str(&token->str[i], bit_len) == 1)
		fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: %s: \"%s\"\n",
			EXECUTABLE_NAME, WARNING_SYNTAX, token->lin, token->col,
			WARNING_INSTRUCTION, WARNING_INSTRUCTION_REGISTER,
			WARNING_OVERFLOW, token->str);
	return (0);
}

static bool	check_immediate_operand_syntax(t_lst* symbol_table, t_token* token, size_t bit_len)
{
	t_lst*	label = lst_find(symbol_table, token->str, cmp_label);
	if (label != NULL)
	{
		if (will_overflow_int((ssize_t)((t_label *)label->content)->line, bit_len) == 1)
			fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: %s: \"%s\"\n",
				EXECUTABLE_NAME, WARNING_SYNTAX, token->lin, token->col,
				WARNING_INSTRUCTION, WARNING_INSTRUCTION_LABEL,
				WARNING_OVERFLOW, token->str);
		return (0);
	}
	if (is_number(token->str) == 0)
	{
		fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: %s: \"%s\"\n",
			EXECUTABLE_NAME, ERROR_SYNTAX, token->lin, token->col,
			ERROR_INSTRUCTION, ERROR_INSTRUCTION_IMMEDIATE,
			ERROR_NOT_NUMBER, token->str);
		return (1);
	}
	else if (will_overflow_str(token->str, bit_len) == 1)
		fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: %s: \"%s\"\n",
			EXECUTABLE_NAME, WARNING_SYNTAX, token->lin, token->col,
			WARNING_INSTRUCTION, WARNING_INSTRUCTION_IMMEDIATE,
			WARNING_OVERFLOW, token->str);
	return (0);
}

static bool	check_condition_operand_syntax(t_isa* isa, t_token* token, size_t bit_len)
{
	size_t*	flag = (size_t *)get_assembling_target(isa, token->str, FLAG);
	if (flag != NULL)
		return (0);
	else if (is_number(token->str) == 0)
	{
		fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: %s: \"%s\"\n",
			EXECUTABLE_NAME, ERROR_SYNTAX, token->lin, token->col,
			ERROR_INSTRUCTION, ERROR_INSTRUCTION_CONDITION,
			ERROR_NOT_NUMBER, token->str);
		return (1);
	}
	ssize_t	number = get_number(token->str);
	if (parr_find(&isa->flags, (void *)&number, cmp_flag) == NULL)
	{
		fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: %s: \"%s\"\n",
			EXECUTABLE_NAME, ERROR_SYNTAX, token->lin, token->col,
			ERROR_INSTRUCTION, ERROR_INSTRUCTION_CONDITION,
			ERROR_INSTRUCTION_CONDITION_FLAG, token->str);
		return (1);
	}
	else if (will_overflow_str(token->str, bit_len) == 1)
		fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: %s: \"%s\"\n",
			EXECUTABLE_NAME, WARNING_SYNTAX, token->lin, token->col,
			WARNING_INSTRUCTION, WARNING_INSTRUCTION_CONDITION,
			WARNING_OVERFLOW, token->str);
	return (0);
}

static t_bitfield*	get_bitfield(t_instruction* instr, size_t i_opword_target)
{
	size_t	i_bitfield = 0, i_opword = 0;
	while (i_opword < i_opword_target
		|| ((t_bitfield *)instr->bitfields.arr)[i_bitfield].type == CONSTANT)
	{
		if (((t_bitfield *)instr->bitfields.arr)[i_bitfield].type != CONSTANT)
			i_opword++;
		i_bitfield++;
	}
	return (&((t_bitfield *)instr->bitfields.arr)[i_bitfield]);
}

static bool	check_operand_syntax(t_data* data, t_instruction* instr, t_token* token,
	size_t i_opword)
{
	t_bitfield*	bitfield = get_bitfield(instr, i_opword);
	if (bitfield->type == REGISTER)
		return (check_register_operand_syntax(&data->isa, token, bitfield->len));
	else if (bitfield->type == IMMEDIATE)
		return (check_immediate_operand_syntax(data->symbol_table, token, bitfield->len));
	else if (bitfield->type == CONDITION)
		return (check_condition_operand_syntax(&data->isa, token, bitfield->len));
	else
		return (0);
}

bool	check_instruction_syntax(t_data* data, t_lst **tokens_ptr)
{
	t_lst*	tokens = *tokens_ptr;
	t_instruction*	instr = (t_instruction *)get_assembling_target(&data->isa,
		((t_token *)tokens->content)->str, INSTRUCTION);
	if (instr == NULL)
		return (0);
	bool	error = 0;
	size_t	i_opword = 0;
	while (tokens->next != NULL && i_opword < instr->n_opwords)
	{
		if (check_operand_syntax(data, instr,
			(t_token *)tokens->next->content, i_opword) == 1)
			error = 1;
		tokens = tokens->next;
		i_opword++;
	}
	*tokens_ptr = tokens->next;
	if (i_opword < instr->n_opwords)
	{
		fprintf(stderr, "%s: %s (%zu:%zu): %s: %s\n",
			EXECUTABLE_NAME, ERROR_SYNTAX,
			((t_token *)tokens->content)->lin, ((t_token *)tokens->content)->col
				+ strlen(((t_token *)tokens->content)->str) + 1,
			ERROR_INSTRUCTION, ERROR_INSTRUCTION_TOO_FEW_ARGS);
		return (1);
	}
	else if (tokens->next != NULL)
	{
		fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: \"%s\"\n",
			EXECUTABLE_NAME, ERROR_SYNTAX,
			((t_token *)tokens->next->content)->lin,
			((t_token *)tokens->next->content)->col, ERROR_INSTRUCTION,
			ERROR_INSTRUCTION_TOO_MANY_ARGS, ((t_token *)tokens->next->content)->str);
		return (1);
	}
	return (error);
}
