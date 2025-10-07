#include <string.h>
#include "lst.h"
#include "data.h"
#include "isa.h"
#include "syntax.h"
#include "tokenization.h"
#include "symbol_table.h"
#include "cmp.h"
#include "nbr.h"
#include "error.h"

static bool	check_register_operand_syntax(t_isa* isa, t_token* token)
{
	if (parr_find(&isa->registers, token->str, cmp_mnemonics) == NULL)
	{
		fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: %s: \"%s\"\n",
			EXECUTABLE_NAME, ERROR_SYNTAX, token->lin, token->col,
			ERROR_INSTRUCTION, ERROR_INSTRUCTION_REGISTER,
			ERROR_INSTRUCTION_OPERAND_MNEMONIC, token->str);
		return (1);
	}
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
	if (will_overflow_str(token->str, bit_len) == 1)
		fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: %s: \"%s\"\n",
			EXECUTABLE_NAME, WARNING_SYNTAX, token->lin, token->col,
			WARNING_INSTRUCTION, WARNING_INSTRUCTION_IMMEDIATE,
			WARNING_OVERFLOW, token->str);
	return (0);
}

static bool	check_flag_operand_syntax(t_isa* isa, t_token* token)
{
	if (parr_find(&isa->flags, token->str, cmp_mnemonics) == NULL)
	{
		fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: %s: \"%s\"\n",
			EXECUTABLE_NAME, ERROR_SYNTAX, token->lin, token->col,
			ERROR_INSTRUCTION, ERROR_INSTRUCTION_FLAG,
			ERROR_INSTRUCTION_OPERAND_MNEMONIC, token->str);
		return (1);
	}
	return (0);
}

static t_bitfield*	get_bitfield(t_instruction* instr, size_t i_opword_target)
{
	size_t	i_bitfield = 0, i_opword = 0;
	while (i_opword < i_opword_target + 1)
	{
		if (((t_bitfield *)instr->bitfields.arr)[i_bitfield].type != CONSTANT)
			i_opword++;
		i_bitfield++;
	}
	return (&((t_bitfield *)instr->bitfields.arr)[i_bitfield - 1]);
}

static bool	check_operand_syntax(t_data* data, t_instruction* instr, t_token* token,
	size_t i_opword)
{
	t_bitfield*	bitfield = get_bitfield(instr, i_opword);
	if (bitfield->type == REGISTER)
		return (check_register_operand_syntax(&data->isa, token));
	if (bitfield->type == IMMEDIATE)
		return (check_immediate_operand_syntax(data->symbol_table, token, bitfield->len));
	return (check_flag_operand_syntax(&data->isa, token));
}

bool	check_instruction_syntax(t_data* data, t_lst **tokens_ptr)
{
	t_lst*	tokens = *tokens_ptr;
	t_instruction*	instr = parr_find(&data->isa.instructions,
		((t_token *)tokens->content)->str, cmp_mnemonics);
	if (instr == NULL)
		return (0);
	*tokens_ptr = lst_last(tokens)->next;
	bool	error = 0;
	size_t	i_opword = 0;
	while (tokens->next != NULL && i_opword < instr->n_opwords)
	{
		tokens = tokens->next;
		if (check_operand_syntax(data, instr, (t_token *)tokens->content, i_opword) == 1)
			error = 1;
		i_opword++;
	}
	if (i_opword < instr->n_opwords)
	{
		fprintf(stderr, "%s: %s (%zu:%zu): %s: %s\n",
			EXECUTABLE_NAME, ERROR_SYNTAX,
			((t_token *)tokens->content)->lin, ((t_token *)tokens->content)->col
				+ strlen(((t_token *)tokens->content)->str) + 1,
			ERROR_INSTRUCTION, ERROR_INSTRUCTION_TOO_FEW_ARGS);
		return (1);
	}
	tokens = tokens->next;
	if (tokens != NULL)
	{
		fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: ",
			EXECUTABLE_NAME, ERROR_SYNTAX,
			((t_token *)tokens->content)->lin, ((t_token *)tokens->content)->col,
			ERROR_INSTRUCTION, ERROR_INSTRUCTION_TOO_MANY_ARGS);
		while (tokens != NULL)
		{
			fprintf(stderr, "\"%s\"", ((t_token *)tokens->content)->str);
			if (tokens->next != NULL)
				fprintf(stderr, ", ");
			tokens = tokens->next;
		}
		fprintf(stderr, "\n");
		return (1);
	}
	return (error);
}
