#include <sys/param.h>
#include <string.h>
#include <ctype.h>
#include "indulc.h"
#include "file.h"
#include "error.h"
#include "token.h"
#include "label.h"
#include "nbr.h"

static bool	write_compiled_instruction(t_file* file, t_parr* instruction)
{
#ifdef COMP_BIN_CHAR
	static char	buffer[9];
	buffer[8] = ' ';
	for (size_t i_byte = 0; i_byte < instruction->len * instruction->obj_size; i_byte++)
	{
		uint8_t	byte = ((uint8_t *)instruction->arr)[i_byte];
		for (size_t i_bit = 0; i_bit < 8; i_bit++)
			buffer[i_bit] = ((byte >> (8 - i_bit - 1)) & 1) + '0';
		if (i_byte + 1 >= instruction->len * instruction->obj_size)
			buffer[8] = '\n';
		fwrite(buffer, sizeof(*buffer), sizeof(buffer), file->stream);
	}
#else
	fwrite(instruction->arr, instruction->obj_size, instruction->len, file->stream);
#endif
	if (ferror(file->stream) != 0)
	{
		fprintf(stderr, "%s: %s: %s: \"%s\"\n", EXECUTABLE_NAME, FUNC_FWRITE,
			ERROR_WRITE_FILE, file->name);
		return (1);
	}
	return (0);
}

static ssize_t	get_register_operand(t_token* token)
{
	size_t	i = 0;
	if (tolower(token->str[i]) == 'r')
		i++;
	return (get_number(&token->str[i]));
}

static ssize_t	get_immediate_operand(t_lst* symbol_table, t_token* token)
{
	t_lst*	label = (t_lst *)lst_find(symbol_table, token->str, cmp_label);
	if (label != NULL)
		return ((ssize_t)((t_label *)label->content)->line);
	else
		return (get_number(token->str));
}

static ssize_t	get_condition_operand(t_isa* isa, t_token* token)
{
	size_t*	flag = (size_t *)get_compilation_target(isa, token->str, FLAG);
	if (flag != NULL)
		return ((ssize_t)*flag);
	else
		return (get_number(token->str));
}

static void	bitshift_buffer(t_parr* buffer, size_t len)
{
	uint8_t	byte;
	size_t	i = 0, diff_byte = len / (buffer->obj_size * 8);
	while (i < buffer->len)
	{
		if (i + diff_byte < buffer->len)
			byte = ((uint8_t *)buffer->arr)[i + diff_byte];
		else
			byte = 0;
		((uint8_t *)buffer->arr)[i] = byte;
		i++;
	}
	size_t	diff_bit = len % (buffer->obj_size * 8);
	if (diff_bit == 0)
		return;
	i = 0;
	while (i + diff_byte < buffer->len)
	{
		if (i + diff_byte + 1 < buffer->len)
			byte = ((uint8_t *)buffer->arr)[i + 1];
		else
			byte = 0;
		((uint8_t *)buffer->arr)[i] = (((uint8_t *)buffer->arr)[i] << diff_bit)
			| (byte >> (buffer->obj_size * 8 - diff_bit));
		i++;
	}
}

static void	add_operand(t_parr* buffer, ssize_t operand, size_t len_bit)
{
	bitshift_buffer(buffer, len_bit);
	size_t	i = buffer->len * buffer->obj_size, limit = i - (len_bit / 8 + (len_bit % 8 != 0));
	while (i > limit)
	{
		((uint8_t *)buffer->arr)[i - 1] = ((uint8_t *)buffer->arr)[i - 1]
			| (operand & build_mask(MIN(len_bit, 8)));
		operand >>= buffer->obj_size * 8;
		len_bit -= buffer->obj_size * 8;
		i--;
	}
}

static bool	encode_instruction(t_data* data, t_lst* tokens, t_instruction* instr,
	t_parr* buffer)
{
	ssize_t	operand;
	size_t	i_opword = 0, i_bitfield = 0;
	tokens = tokens->next;
	while (i_opword < instr->n_opwords)
	{
		t_bitfield*	bitfield = &((t_bitfield *)instr->bitfields.arr)[i_bitfield];
		if (bitfield->type == REGISTER)
			operand = get_register_operand((t_token *)tokens->content);
		else if (bitfield->type == IMMEDIATE)
			operand = get_immediate_operand(data->symbol_table,
				(t_token *)tokens->content);
		else if (bitfield->type == CONDITION)
			operand = get_condition_operand(&data->isa, (t_token *)tokens->content);
		else
			operand = bitfield->constant;
		add_operand(buffer, operand, bitfield->len);
		if (bitfield->type != CONSTANT)
		{
			tokens = tokens->next;
			i_opword++;
		}
		i_bitfield++;
	}
	return (write_compiled_instruction(&data->files[OUTFILE_PROGRAM], buffer));
}

static bool	allocate_writing_buffer(size_t instruction_length, t_parr* buffer)
{
	buffer->obj_size = sizeof(uint8_t);
	buffer->len = instruction_length / (buffer->obj_size * 8)
		+ (instruction_length % (buffer->obj_size * 8) != 0);
	buffer->arr = malloc(buffer->len);
	if (buffer->arr == NULL)
	{
		fprintf(stderr, "%s: %s: %s\n",
			EXECUTABLE_NAME, FUNC_MALLOC, ERROR_FAILED_ALLOC);
		return (1);
	}
	return (0);
}

bool	machine_code_generation(t_data* data)
{
	t_parr	buffer;
	if (allocate_writing_buffer(data->isa.instruction_length, &buffer) == 1)
		return (1);
	t_lst*	tokens_lin = data->tokens;
	while (tokens_lin != NULL)
	{
		t_lst*	tokens_col = (t_lst *)tokens_lin->content;
		if (is_label(tokens_col) == 1)
			tokens_col = tokens_col->next->next;
		if (tokens_col != NULL)
		{
			bzero(buffer.arr, buffer.len * buffer.obj_size);
			t_instruction*	instr = (t_instruction *)get_compilation_target(&data->isa,
				((t_token *)tokens_col->content)->str, INSTRUCTION);
			if (instr != NULL
				&& encode_instruction(data, tokens_col, instr, &buffer) == 1)
			{
				free(buffer.arr);
				return (1);
			}
		}
		tokens_lin = tokens_lin->next;
	}
	free(buffer.arr);
	return (0);
}
