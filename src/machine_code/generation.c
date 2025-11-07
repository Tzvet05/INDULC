#include <sys/param.h>
#include <strings.h>
#include <stdlib.h>
#include "lst.h"
#include "bit.h"
#include "data.h"
#include "isa.h"
#include "tokenization.h"
#include "machine_code.h"
#include "cmp.h"
#include "is.h"
#include "error.h"

static void	add_operand(t_parr *buffer, size_t i_instr, size_t i_start_bit, ssize_t operand,
	size_t len_operand)
{
	size_t	i_bit = i_start_bit + len_operand - 1, i_byte = i_bit / 8;
	while (i_bit > i_start_bit)
	{
		size_t	i_start_mask = i_bit & 0xFFFFFFFFFFFFFFF8,
			i_end_mask = i_start_mask + 7,
			len_part = MIN(i_bit, i_end_mask) - MAX(i_start_bit, i_start_mask) + 1;
		((uint8_t *)buffer->arr)[i_instr * buffer->obj_size + i_byte]
			|= (uint8_t)((uint64_t)operand & build_mask(len_part))
			<< (i_end_mask - i_bit);
		operand >>= len_part;
		i_bit -= MIN(i_bit, len_part);
		i_byte--;
	}
}

static void	encode_instruction(t_data *data, t_lst *tokens, t_instruction *instr,
	t_parr *buffer, size_t i_instr)
{
	ssize_t	operand;
	size_t	i_bit = ((data->isa.instruction_length + 7) & 0xFFFFFFFFFFFFFFF8)
		- data->isa.instruction_length;
	for (size_t i_bitfield = 0; i_bitfield < instr->bitfields.len; i_bitfield++)
	{
		t_bitfield	*bitfield = &((t_bitfield *)instr->bitfields.arr)[i_bitfield];
		if (bitfield->type == REGISTER)
			operand = (ssize_t)((t_register *)parr_find(&data->isa.registers,
				((t_token *)tokens->content)->str, cmp_mnemonics))->index;
		else if (bitfield->type == IMMEDIATE)
			operand = get_immediate_operand(data->symbol_table,
				(t_token *)tokens->content);
		else if (bitfield->type == FLAG)
			operand = (ssize_t)((t_flag *)parr_find(&data->isa.flags,
				((t_token *)tokens->content)->str, cmp_mnemonics))->code;
		else
			operand = bitfield->value;
		add_operand(buffer, i_instr, i_bit, operand, bitfield->len);
		if (bitfield->type != CONSTANT)
			tokens = tokens->next;
		i_bit += bitfield->len;
	}
}

static bool	allocate_instructions_buffer(t_isa *isa, t_lst *tokens, t_parr *buffer)
{
	buffer->obj_size = (isa->instruction_length + 7) / 8;
	buffer->len = count_instructions(isa, tokens);
	buffer->arr = malloc(buffer->len * buffer->obj_size);
	if (buffer->arr == NULL)
	{
		fprintf(stderr, "%s: %s: %s: %s\n",
			EXECUTABLE_NAME, LIB_LIBC, FUNC_MALLOC, ERROR_FAILED_ALLOC);
		return (1);
	}
	bzero(buffer->arr, buffer->len * buffer->obj_size);
	return (0);
}

bool	generate_machine_code(t_data *data)
{
	t_parr	buffer;
	if (allocate_instructions_buffer(&data->isa, data->tokens, &buffer) == 1)
		return (1);
	size_t	i_instr = 0;
	t_lst	*tokens_lin = data->tokens;
	while (tokens_lin != NULL)
	{
		t_lst	*tokens_col = tokens_lin->content;
		if (is_label(tokens_col) == 1)
			tokens_col = tokens_col->next->next;
		if (tokens_col != NULL)
		{
			t_instruction	*instr = parr_find(&data->isa.instructions,
				((t_token *)tokens_col->content)->str, cmp_mnemonics);
			if (instr != NULL)
			{
				encode_instruction(data, tokens_col->next, instr, &buffer, i_instr);
				i_instr++;
			}
		}
		tokens_lin = tokens_lin->next;
	}
	data->output.machine_code = buffer;
	return (0);
}
