#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include "indulc.h"
#include "file.h"
#include "error.h"
#include "token.h"
#include "label.h"

static bool	write_compiled_instruction(t_file* file, uint32_t compiled_instruction)
{
	fwrite(&compiled_instruction, 1, sizeof(uint32_t), file->stream);
	if (ferror(file->stream) != 0)
	{
		fprintf(stderr, "%s: %s: %s: \"%s\"\n", EXECUTABLE_NAME, FUNC_FWRITE,
			ERROR_WRITE_FILE, file->name);
		return (1);
	}
	return (0);
}

static uint32_t	get_register_operand(t_token* token)
{
	size_t	i = 0;
	if (tolower(token->str[i]) == 'r')
		i++;
	int32_t	number = (int32_t)get_number(&token->str[i]);
	uint32_t	buffer;
	memcpy(&buffer, &number, sizeof(uint32_t));
	return (buffer);
}

static uint32_t	get_immediate_operand(t_lst* symbol_table, t_token* token)
{
	t_lst*	label = (t_lst *)lst_find(symbol_table, token->str, cmp_label);
	int32_t	number;
	if (label != NULL)
		number = (int32_t)((t_label *)label->content)->line;
	else
		number = (int32_t)get_number(token->str);
	uint32_t	buffer;
	memcpy(&buffer, &number, sizeof(uint32_t));
	return (buffer);
}

static uint32_t	get_condition_operand(t_isa* isa, t_token* token)
{
	t_flag*	flag = (t_flag *)get_compilation_target(isa, token->str, FLAG);
	int32_t	number;
	if (flag != NULL)
		number = (int32_t)flag->condition_code;
	else
		number = (int32_t)get_number(token->str);
	uint32_t	buffer;
	memcpy(&buffer, &number, sizeof(uint32_t));
	return (buffer);
}

static bool	encode_instruction(t_data* data, t_lst* tokens, t_instruction* instr)
{
	uint32_t	operand = instr->opcode;
	uint32_t	compiled_instruction = operand
		& (uint32_t)build_mask(((t_bitfield *)instr->bitfields.arr)[0].len);
	size_t	i = 1;
	tokens = tokens->next;
	while (i < instr->bitfields.len)
	{
		t_bitfield*	bitfield = &((t_bitfield *)instr->bitfields.arr)[i];
		if (bitfield->type == REGISTER)
			operand = get_register_operand((t_token *)tokens->content);
		else if (bitfield->type == IMMEDIATE)
			operand = get_immediate_operand(data->symbol_table,
				(t_token *)tokens->content);
		else if (bitfield->type == CONDITION)
			operand = get_condition_operand(&data->isa, (t_token *)tokens->content);
		else
			operand = 0;
		compiled_instruction <<= bitfield->len;
		compiled_instruction |= operand & (uint32_t)build_mask(bitfield->len);
		if (bitfield->type != UNUSED)
			tokens = tokens->next;
		i++;
	}
	return (write_compiled_instruction(&((t_file *)data->files.arr)[OUTFILE_PROGRAM],
		compiled_instruction));
}

bool	machine_code_generation(t_data* data)
{
	t_lst*	tokens_lin = data->tokens;
	while (tokens_lin != NULL)
	{
		t_lst*	tokens_col = (t_lst *)tokens_lin->content;
		if (is_label(tokens_col) == 1)
			tokens_col = tokens_col->next->next;
		if (tokens_col != NULL)
		{
			t_instruction*	instr = (t_instruction *)get_compilation_target(&data->isa,
				((t_token *)tokens_col->content)->str, INSTRUCTION);
			if (instr != NULL && encode_instruction(data, tokens_col, instr) == 1)
				return (1);
		}
		tokens_lin = tokens_lin->next;
	}
	return (0);
}
