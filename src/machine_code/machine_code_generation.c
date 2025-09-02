#include <stdlib.h>
#include <string.h>
#include <sys/param.h>
#include "files.h"
#include "arguments.h"
#include "symbol_table.h"
#include "machine_code.h"
#include "cmp.h"
#include "bit.h"
#include "error.h"

static bool	write_instruction(t_data* data, t_parr* instruction)
{
	if (data->options & OPTION_OUTPUT_CHARS)
	{
		static char	buffer[9];
		buffer[8] = ' ';
		for (size_t i_byte = 0; i_byte < instruction->len * instruction->obj_size; i_byte++)
		{
			uint8_t	byte = ((uint8_t *)instruction->arr)[i_byte];
			for (size_t i_bit = 0; i_bit < 8; i_bit++)
				buffer[i_bit] = ((byte >> (8 - i_bit - 1)) & 1) + '0';
			if (i_byte + 1 >= instruction->len * instruction->obj_size)
				buffer[8] = '\n';
			fwrite(buffer, sizeof(*buffer), sizeof(buffer),
				data->files[OUTFILE_PROGRAM].stream);
		}
	}
	else
		fwrite(instruction->arr, instruction->obj_size, instruction->len,
			data->files[OUTFILE_PROGRAM].stream);
	if (ferror(data->files[OUTFILE_PROGRAM].stream) != 0)
	{
		fprintf(stderr, "%s: %s: %s: \"%s\"\n",
			EXECUTABLE_NAME, FUNC_FWRITE, ERROR_WRITE_FILE,
			data->files[OUTFILE_PROGRAM].name);
		return (1);
	}
	return (0);
}

static void	add_operand(t_parr* buffer, size_t i_bit_start, ssize_t operand, size_t len_operand)
{
	size_t	i_bit = i_bit_start + len_operand - 1, i_byte = i_bit / 8;
	while (i_bit > i_bit_start)
	{
		size_t	i_bit_byte_start = i_bit & 0xFFFFFFFFFFFFFFF8,
			i_bit_byte_end = i_bit_byte_start + 7, len_part = MIN(i_bit, i_bit_byte_end)
				- MAX(i_bit_start, i_bit_byte_start) + 1;
		((uint8_t *)buffer->arr)[i_byte] |= (operand & build_mask(len_part))
			<< (i_bit_byte_end - i_bit);
		operand >>= len_part;
		i_bit -= MIN(i_bit, len_part);
		i_byte--;
	}
}

static bool	encode_instruction(t_data* data, t_lst* tokens, t_instruction* instr,
	t_parr* buffer, size_t i_bit)
{
	tokens = tokens->next;
	for (size_t i_bitfield = 0; i_bitfield < instr->bitfields.len; i_bitfield++)
	{
		ssize_t	operand;
		t_bitfield*	bitfield = &((t_bitfield *)instr->bitfields.arr)[i_bitfield];
		if (bitfield->type == REGISTER)
			operand = ((t_register *)parr_find(&data->isa.registers,
				((t_token *)tokens->content)->str, cmp_mnemonics))->index;
		else if (bitfield->type == IMMEDIATE)
			operand = get_immediate_operand(data->symbol_table,
				(t_token *)tokens->content);
		else if (bitfield->type == FLAG)
			operand = ((t_flag *)parr_find(&data->isa.flags,
				((t_token *)tokens->content)->str, cmp_mnemonics))->code;
		else
			operand = bitfield->value;
		add_operand(buffer, i_bit, operand, bitfield->len);
		if (bitfield->type != CONSTANT)
			tokens = tokens->next;
		i_bit += bitfield->len;
	}
	return (write_instruction(data, buffer));
}

static bool	allocate_writing_buffer(size_t instruction_length, t_parr* buffer)
{
	buffer->obj_size = sizeof(uint8_t);
	buffer->len = (instruction_length + (buffer->obj_size * 8 - 1)) / (buffer->obj_size * 8);
	buffer->arr = malloc(buffer->len);
	if (buffer->arr == NULL)
	{
		fprintf(stderr, "%s: %s: %s\n",
			EXECUTABLE_NAME, FUNC_MALLOC, ERROR_FAILED_ALLOC);
		return (1);
	}
	return (0);
}

bool	generate_machine_code(t_data* data)
{
	t_parr	buffer;
	if (allocate_writing_buffer(data->isa.instruction_length, &buffer) == 1)
		return (1);
	size_t	i_bit_start = (buffer.len * buffer.obj_size * 8) - data->isa.instruction_length;
	t_lst*	tokens_lin = data->tokens;
	while (tokens_lin != NULL)
	{
		t_lst*	tokens_col = (t_lst *)tokens_lin->content;
		if (is_label(tokens_col) == 1)
			tokens_col = tokens_col->next->next;
		if (tokens_col != NULL)
		{
			t_instruction*	instr = parr_find(&data->isa.instructions,
				((t_token *)tokens_col->content)->str, cmp_mnemonics);
			if (instr != NULL)
			{
				bzero(buffer.arr, buffer.len * buffer.obj_size);
				if (encode_instruction(data, tokens_col, instr, &buffer,
					i_bit_start) == 1)
				{
					free(buffer.arr);
					return (1);
				}
			}
		}
		tokens_lin = tokens_lin->next;
	}
	free(buffer.arr);
	return (0);
}
