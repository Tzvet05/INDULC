#include <stdlib.h>
#include <string.h>
#include "cJSON.h"
#include "isa.h"
#include "error.h"

static bool	get_instructions(t_isa *isa, const cJSON *instructions)
{
	isa->instructions.len = (size_t)cJSON_GetArraySize(instructions);
	isa->instructions.obj_size = sizeof(t_instruction);
	isa->instructions.arr = malloc(isa->instructions.len * isa->instructions.obj_size);
	if (isa->instructions.arr == NULL)
	{
		isa->instructions.len = 0;
		return (1);
	}
	size_t	i_instruction = 0;
	const cJSON	*instruction;
	cJSON_ArrayForEach(instruction, instructions)
	{
		const cJSON	*item_instruction = cJSON_GetObjectItemCaseSensitive(instruction,
			JSON_INSTRUCTION_MNEMONICS);
		((t_instruction *)isa->instructions.arr)[i_instruction].mnemonics.len
			= (size_t)cJSON_GetArraySize(item_instruction);
		((t_instruction *)isa->instructions.arr)[i_instruction].mnemonics.obj_size
			= sizeof(char *);
		((t_instruction *)isa->instructions.arr)[i_instruction].mnemonics.arr
			= malloc(((t_instruction *)isa->instructions.arr)
			[i_instruction].mnemonics.len * ((t_instruction *)isa->instructions.arr)
			[i_instruction].mnemonics.obj_size);
		if (((t_instruction *)isa->instructions.arr)[i_instruction].mnemonics.arr == NULL)
		{
			isa->instructions.len = i_instruction + 1;
			((t_instruction *)isa->instructions.arr)[i_instruction].mnemonics.len = 0;
			((t_instruction *)isa->instructions.arr)[i_instruction].bitfields
				= (t_parr){0};
			return (1);
		}
		size_t	i_mnemonic = 0;
		const cJSON	*mnemonic;
		cJSON_ArrayForEach(mnemonic, item_instruction)
		{
			((char **)((t_instruction *)isa->instructions.arr)
				[i_instruction].mnemonics.arr)[i_mnemonic]
				= strdup(cJSON_GetStringValue(mnemonic));
			if (((char **)((t_instruction *)isa->instructions.arr)
				[i_instruction].mnemonics.arr)[i_mnemonic] == NULL)
			{
				isa->instructions.len = i_instruction + 1;
				((t_instruction *)isa->instructions.arr)
					[i_instruction].mnemonics.len = i_mnemonic + 1;
				((t_instruction *)isa->instructions.arr)
					[i_instruction].bitfields = (t_parr){0};
				return (1);
			}
			i_mnemonic++;
		}
		item_instruction = cJSON_GetObjectItemCaseSensitive(instruction,
			JSON_INSTRUCTION_BITFIELDS);
		((t_instruction *)isa->instructions.arr)[i_instruction].bitfields.len
			= (size_t)cJSON_GetArraySize(item_instruction);
		((t_instruction *)isa->instructions.arr)[i_instruction].bitfields.obj_size
			= sizeof(t_bitfield);
		((t_instruction *)isa->instructions.arr)[i_instruction].bitfields.arr
			= malloc(((t_instruction *)isa->instructions.arr)[i_instruction]
			.bitfields.len * ((t_instruction *)isa->instructions.arr)[i_instruction]
			.bitfields.obj_size);
		if (((t_instruction *)isa->instructions.arr)[i_instruction].bitfields.arr == NULL)
		{
			isa->instructions.len = i_instruction + 1;
			((t_instruction *)isa->instructions.arr)[i_instruction].bitfields.len = 0;
			((t_instruction *)isa->instructions.arr)
				[i_instruction].bitfields.obj_size = 0;
			return (1);
		}
		size_t	i_bitfield = 0;
		const cJSON	*bitfield;
		cJSON_ArrayForEach(bitfield, item_instruction)
		{
			const cJSON	*item_bitfield = cJSON_GetObjectItemCaseSensitive(bitfield,
				JSON_INSTRUCTION_BITFIELD_LEN);
			double	number_value = cJSON_GetNumberValue(item_bitfield);
			((t_bitfield *)((t_instruction *)isa->instructions.arr)[i_instruction]
				.bitfields.arr)[i_bitfield].len = (size_t)number_value;
			item_bitfield = cJSON_GetObjectItemCaseSensitive(bitfield,
				JSON_INSTRUCTION_BITFIELD_TYPE);
			ssize_t	bitfield_type
				= get_bitfield_type(cJSON_GetStringValue(item_bitfield));
			((t_bitfield *)((t_instruction *)isa->instructions.arr)[i_instruction]
				.bitfields.arr)[i_bitfield].type = (t_bitfield_type)bitfield_type;
			if (((t_bitfield *)((t_instruction *)isa->instructions.arr)[i_instruction]
				.bitfields.arr)[i_bitfield].type == CONSTANT
				&& cJSON_HasObjectItem(bitfield,
				JSON_INSTRUCTION_BITFIELD_VALUE) != 0)
			{
				item_bitfield = cJSON_GetObjectItemCaseSensitive(bitfield,
				JSON_INSTRUCTION_BITFIELD_VALUE);
				number_value = cJSON_GetNumberValue(item_bitfield);
				((t_bitfield *)((t_instruction *)isa->instructions.arr)
					[i_instruction].bitfields.arr)[i_bitfield].value
					= (ssize_t)number_value;
			}
			else
				((t_bitfield *)((t_instruction *)isa->instructions.arr)
					[i_instruction].bitfields.arr)[i_bitfield].value = 0;
			i_bitfield++;
		}
		i_instruction++;
	}
	return (0);
}

static bool	get_flags(t_isa *isa, const cJSON *flags)
{
	isa->flags.len = (size_t)cJSON_GetArraySize(flags);
	isa->flags.obj_size = sizeof(t_flag);
	isa->flags.arr = malloc(isa->flags.len * isa->flags.obj_size);
	if (isa->flags.arr == NULL)
	{
		isa->flags.len = 0;
		return (1);
	}
	size_t	i_flag = 0;
	const cJSON	*flag;
	cJSON_ArrayForEach(flag, flags)
	{
		const cJSON	*item_flag = cJSON_GetObjectItemCaseSensitive(flag,
			JSON_FLAG_MNEMONICS);
		((t_flag *)isa->flags.arr)[i_flag].mnemonics.len =
			(size_t)cJSON_GetArraySize(item_flag);
		((t_flag *)isa->flags.arr)[i_flag].mnemonics.obj_size = sizeof(char *);
		((t_flag *)isa->flags.arr)[i_flag].mnemonics.arr =
			malloc(((t_flag *)isa->flags.arr)[i_flag].mnemonics.len
			* ((t_flag *)isa->flags.arr)[i_flag].mnemonics.obj_size);
		if (((t_flag *)isa->flags.arr)[i_flag].mnemonics.arr == NULL)
		{
			isa->flags.len = i_flag + 1;
			((t_flag *)isa->flags.arr)[i_flag].mnemonics.len = 0;
			return (1);
		}
		size_t	i_mnemonic = 0;
		const cJSON	*mnemonic;
		cJSON_ArrayForEach(mnemonic, item_flag)
		{
			((char **)((t_flag *)isa->flags.arr)[i_flag].mnemonics.arr)[i_mnemonic]
				= strdup(cJSON_GetStringValue(mnemonic));
			if (((char **)((t_flag *)isa->flags.arr)[i_flag].mnemonics.arr)[i_mnemonic]
				== NULL)
			{
				isa->flags.len = i_flag + 1;
				((t_flag *)isa->flags.arr)[i_flag].mnemonics.len = i_mnemonic + 1;
				return (1);
			}
			i_mnemonic++;
		}
		item_flag = cJSON_GetObjectItemCaseSensitive(flag, JSON_FLAG_CODE);
		double	number_value = cJSON_GetNumberValue(item_flag);
		((t_flag *)isa->flags.arr)[i_flag].code = (size_t)number_value;
		i_flag++;
	}
	return (0);
}

static bool	get_registers(t_isa *isa, const cJSON *registers)
{
	isa->registers.len = (size_t)cJSON_GetArraySize(registers);
	isa->registers.obj_size = sizeof(t_register);
	isa->registers.arr = malloc(isa->registers.len * isa->registers.obj_size);
	if (isa->registers.arr == NULL)
	{
		isa->registers.len = 0;
		return (1);
	}
	size_t	i_register = 0;
	const cJSON	*_register;
	cJSON_ArrayForEach(_register, registers)
	{
		const cJSON	*item_register = cJSON_GetObjectItemCaseSensitive(_register,
			JSON_REGISTER_MNEMONICS);
		((t_register *)isa->registers.arr)[i_register].mnemonics.len
			= (size_t)cJSON_GetArraySize(item_register);
		((t_register *)isa->registers.arr)[i_register].mnemonics.obj_size = sizeof(char *);
		((t_register *)isa->registers.arr)[i_register].mnemonics.arr
			= malloc(((t_register *)isa->registers.arr)[i_register].mnemonics.len
				* ((t_register *)isa->registers.arr)
					[i_register].mnemonics.obj_size);
		if (((t_register *)isa->registers.arr)[i_register].mnemonics.arr == NULL)
		{
			((t_register *)isa->registers.arr)[i_register].mnemonics.len = 0;
			isa->registers.len = i_register + 1;
			return (1);
		}
		size_t	i_mnemonic = 0;
		const cJSON	*mnemonic;
		cJSON_ArrayForEach(mnemonic, item_register)
	{
			((char **)((t_register *)isa->registers.arr)
				[i_register].mnemonics.arr)[i_mnemonic]
				= strdup(cJSON_GetStringValue(mnemonic));
			if (((char **)((t_register *)isa->registers.arr)
				[i_register].mnemonics.arr)[i_mnemonic] == NULL)
			{
				((t_register *)isa->registers.arr)[i_register].mnemonics.len
					= i_mnemonic + 1;
				isa->registers.len = i_register + 1;
				return (1);
			}
			i_mnemonic++;
		}
		item_register = cJSON_GetObjectItemCaseSensitive(_register, JSON_REGISTER_INDEX);
		double	item_value = cJSON_GetNumberValue(item_register);
		((t_register *)isa->registers.arr)[i_register].index = (size_t)item_value;
		i_register++;
	}
	return (0);
}

bool	init_isa(t_isa *isa, const cJSON *json_isa)
{
	const cJSON	*item_isa = cJSON_GetObjectItemCaseSensitive(json_isa,
		JSON_INSTRUCTION_LENGTH);
	double	item_value = cJSON_GetNumberValue(item_isa);
	isa->instruction_length = (size_t)item_value;
	item_isa = cJSON_GetObjectItemCaseSensitive(json_isa, JSON_REGISTERS);
	if (get_registers(isa, item_isa) == 1)
		return (1);
	item_isa = cJSON_GetObjectItemCaseSensitive(json_isa, JSON_INSTRUCTIONS);
	if (get_instructions(isa, item_isa) == 1)
		return (1);
	item_isa = cJSON_GetObjectItemCaseSensitive(json_isa, JSON_FLAGS);
	return (get_flags(isa, item_isa));
}
