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

static bool	check_register_operand_syntax(isa_t *isa, token_t *token)
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

static bool	check_immediate_operand_syntax(lst_t *symbol_table, token_t *token, size_t bit_len)
{
	lst_t	*label = lst_find(symbol_table, token->str, cmp_label);
	if (label != NULL)
	{
		if (will_overflow_int((ssize_t)((label_t *)label->content)->line, bit_len) == 1)
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

static bool	check_flag_operand_syntax(isa_t *isa, token_t *token)
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

static bitfield_t	*get_bitfield(instruction_t *instr, size_t i_opword_target)
{
	size_t	i_bitfield = 0, i_opword = 0;
	while (i_opword < i_opword_target + 1)
	{
		if (((bitfield_t *)instr->bitfields.arr)[i_bitfield].type != CONSTANT)
			i_opword++;
		i_bitfield++;
	}
	return (&((bitfield_t *)instr->bitfields.arr)[i_bitfield - 1]);
}

static bool	check_operand_syntax(data_t *data, instruction_t *instr, token_t *token,
	size_t i_opword)
{
	bitfield_t	*bitfield = get_bitfield(instr, i_opword);
	if (bitfield->type == REGISTER)
		return (check_register_operand_syntax(&data->isa, token));
	if (bitfield->type == IMMEDIATE)
		return (check_immediate_operand_syntax(data->symbol_table, token, bitfield->len));
	return (check_flag_operand_syntax(&data->isa, token));
}

bool	check_instruction_syntax(data_t *data, lst_t **tokens_ptr)
{
	lst_t	*tokens = *tokens_ptr;
	instruction_t	*instr = parr_find(&data->isa.instructions,
		((token_t *)tokens->content)->str, cmp_mnemonics);
	if (instr == NULL)
		return (0);
	*tokens_ptr = lst_last(tokens)->next;
	bool	error = 0;
	size_t	i_opword = 0;
	while (tokens->next != NULL && i_opword < instr->n_opwords)
	{
		tokens = tokens->next;
		if (check_operand_syntax(data, instr, tokens->content, i_opword) == 1)
			error = 1;
		i_opword++;
	}
	if (i_opword < instr->n_opwords)
	{
		fprintf(stderr, "%s: %s (%zu:%zu): %s: %s\n",
			EXECUTABLE_NAME, ERROR_SYNTAX,
			((token_t *)tokens->content)->lin, ((token_t *)tokens->content)->col
				+ strlen(((token_t *)tokens->content)->str) + 1,
			ERROR_INSTRUCTION, ERROR_INSTRUCTION_TOO_FEW_ARGS);
		return (1);
	}
	tokens = tokens->next;
	if (tokens != NULL)
	{
		fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: ",
			EXECUTABLE_NAME, ERROR_SYNTAX,
			((token_t *)tokens->content)->lin, ((token_t *)tokens->content)->col,
			ERROR_INSTRUCTION, ERROR_INSTRUCTION_TOO_MANY_ARGS);
		while (tokens != NULL)
		{
			fprintf(stderr, "\"%s\"", ((token_t *)tokens->content)->str);
			if (tokens->next != NULL)
				fprintf(stderr, ", ");
			tokens = tokens->next;
		}
		fprintf(stderr, "\n");
		return (1);
	}
	return (error);
}
