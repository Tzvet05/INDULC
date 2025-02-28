#include <string.h>
#include "cJSON.h"
#include "indulc.h"
#include "error.h"

static bool	get_instructions(t_isa* isa, const cJSON* instructions)
{
	isa->instructions.len = cJSON_GetArraySize(instructions);
	isa->instructions.obj_size = sizeof(t_instruction);
	isa->instructions.arr = malloc(isa->instructions.len * isa->instructions.obj_size);
	if (isa->instructions.arr == NULL)
	{
		isa->instructions.len = 0;
		isa->mnemonics.len = 0;
		return (1);
	}
	size_t	i_instruction = 0;
	const cJSON*	instruction;
	cJSON_ArrayForEach(instruction, instructions)
	{
		((t_mnemonic *)isa->mnemonics.arr)[i_instruction].compilation_target
			= (void *)&((t_instruction *)isa->instructions.arr)[i_instruction];
		((t_mnemonic *)isa->mnemonics.arr)[i_instruction].type = INSTRUCTION;
		const cJSON*	item_instruction = cJSON_GetObjectItemCaseSensitive(instruction,
			JSON_INSTRUCTION_MNEMONICS);
		((t_mnemonic *)isa->mnemonics.arr)[i_instruction].mnemonics.len
			= cJSON_GetArraySize(item_instruction);
		((t_mnemonic *)isa->mnemonics.arr)[i_instruction].mnemonics.obj_size
			= sizeof(char *);
		((t_mnemonic *)isa->mnemonics.arr)[i_instruction].mnemonics.arr
			= malloc(((t_mnemonic *)isa->mnemonics.arr)[i_instruction].mnemonics.len
			* ((t_mnemonic *)isa->mnemonics.arr)[i_instruction].mnemonics.obj_size);
		if (((t_mnemonic *)isa->mnemonics.arr)[i_instruction].mnemonics.arr == NULL)
		{
			isa->instructions.len = i_instruction + 1;
			((t_instruction *)isa->instructions.arr)[i_instruction].bitfields.len = 0;
			((t_instruction *)isa->instructions.arr)[i_instruction].bitfields.arr
				= NULL;
			isa->mnemonics.len = i_instruction + 1;
			((t_mnemonic *)isa->mnemonics.arr)[i_instruction].mnemonics.len = 0;
			return (1);
		}
		size_t	i_mnemonic = 0;
		const cJSON*	mnemonic;
		cJSON_ArrayForEach(mnemonic, item_instruction)
		{
			((char **)((t_mnemonic *)isa->mnemonics.arr)[i_instruction]
				.mnemonics.arr)[i_mnemonic]
				= strdup(cJSON_GetStringValue(mnemonic));
			if (((char **)((t_mnemonic *)isa->mnemonics.arr)[i_instruction]
				.mnemonics.arr)[i_mnemonic] == NULL)
			{
				isa->instructions.len = i_instruction + 1;
				((t_instruction *)isa->instructions.arr)[i_instruction]
					.bitfields.len = 0;
				((t_instruction *)isa->instructions.arr)[i_instruction]
					.bitfields.arr = NULL;
				isa->mnemonics.len = i_instruction + 1;
				((t_mnemonic *)isa->mnemonics.arr)[i_instruction].mnemonics.len
					= i_mnemonic + 1;
				return (1);
			}
			i_mnemonic++;
		}
		item_instruction = cJSON_GetObjectItemCaseSensitive(instruction,
			JSON_INSTRUCTION_BITFIELDS);
		((t_instruction *)isa->instructions.arr)[i_instruction].bitfields.len
			= cJSON_GetArraySize(item_instruction);
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
			isa->mnemonics.len = i_instruction + 1;
			return (1);
		}
		size_t	i_bitfield = 0;
		const cJSON*	bitfield;
		cJSON_ArrayForEach(bitfield, item_instruction)
		{
			const cJSON*	item_bitfield = cJSON_GetObjectItemCaseSensitive(bitfield,
				JSON_INSTRUCTION_BITFIELD_LEN);
			((t_bitfield *)((t_instruction *)isa->instructions.arr)[i_instruction]
				.bitfields.arr)[i_bitfield].len
				= (size_t)cJSON_GetNumberValue(item_bitfield);
			item_bitfield = cJSON_GetObjectItemCaseSensitive(bitfield,
				JSON_INSTRUCTION_BITFIELD_TYPE);
			((t_bitfield *)((t_instruction *)isa->instructions.arr)[i_instruction]
				.bitfields.arr)[i_bitfield].type = (t_bitfield_type)
				get_bitfield_type(cJSON_GetStringValue(item_bitfield));
			if (((t_bitfield *)((t_instruction *)isa->instructions.arr)[i_instruction]
				.bitfields.arr)[i_bitfield].type == CONSTANT
				&& cJSON_HasObjectItem(bitfield,
				JSON_INSTRUCTION_BITFIELD_CONSTANT) != 0)
			{
				item_bitfield = cJSON_GetObjectItemCaseSensitive(bitfield,
				JSON_INSTRUCTION_BITFIELD_CONSTANT);
				((t_bitfield *)((t_instruction *)isa->instructions.arr)
					[i_instruction].bitfields.arr)[i_bitfield].constant
					= (ssize_t)cJSON_GetNumberValue(item_bitfield);
			}
			else
				((t_bitfield *)((t_instruction *)isa->instructions.arr)
					[i_instruction].bitfields.arr)[i_bitfield].constant = 0;
			i_bitfield++;
		}
		i_instruction++;
	}
	return (0);
}

static bool	get_flags(t_isa* isa, const cJSON* flags)
{
	isa->flags.len = cJSON_GetArraySize(flags);
	isa->flags.obj_size = sizeof(size_t);
	isa->flags.arr = malloc(isa->flags.len * isa->flags.obj_size);
	if (isa->flags.arr == NULL)
	{
		isa->flags.len = 0;
		isa->mnemonics.len = isa->instructions.len;
		return (1);
	}
	size_t	i_flag = 0;
	const cJSON*	flag;
	cJSON_ArrayForEach(flag, flags)
	{
		((t_mnemonic *)isa->mnemonics.arr)[isa->instructions.len
			+ i_flag].compilation_target = (void *)&((size_t *)isa->flags.arr)[i_flag];
		((t_mnemonic *)isa->mnemonics.arr)[isa->instructions.len + i_flag].type = FLAG;
		const cJSON*	item_flag = cJSON_GetObjectItemCaseSensitive(flag,
			JSON_FLAG_MNEMONICS);
		((t_mnemonic *)isa->mnemonics.arr)[isa->instructions.len + i_flag].mnemonics.len
			= cJSON_GetArraySize(item_flag);
		((t_mnemonic *)isa->mnemonics.arr)[isa->instructions.len + i_flag]
			.mnemonics.obj_size = sizeof(char *);
		((t_mnemonic *)isa->mnemonics.arr)[isa->instructions.len + i_flag].mnemonics.arr
			= malloc(((t_mnemonic *)isa->mnemonics.arr)[isa->instructions.len
			+ i_flag].mnemonics.len
			* ((t_mnemonic *)isa->mnemonics.arr)[isa->instructions.len
			+ i_flag].mnemonics.obj_size);
		if (((t_mnemonic *)isa->mnemonics.arr)[isa->instructions.len
			+ i_flag].mnemonics.arr == NULL)
		{
			isa->flags.len = i_flag + 1;
			isa->mnemonics.len = isa->instructions.len + i_flag + 1;
			((t_mnemonic *)isa->mnemonics.arr)[isa->instructions.len + i_flag]
				.mnemonics.len = 0;
			return (1);
		}
		size_t	i_mnemonic = 0;
		const cJSON*	mnemonic;
		cJSON_ArrayForEach(mnemonic, item_flag)
		{
			((char **)((t_mnemonic *)isa->mnemonics.arr)[isa->instructions.len
				+ i_flag].mnemonics.arr)[i_mnemonic]
				= strdup(cJSON_GetStringValue(mnemonic));
			if (((char **)((t_mnemonic *)isa->mnemonics.arr)[isa->instructions.len
				+ i_flag].mnemonics.arr)[i_mnemonic] == NULL)
			{
				isa->flags.len = i_flag + 1;
				isa->mnemonics.len = isa->instructions.len + i_flag + 1;
				((t_mnemonic *)isa->mnemonics.arr)[isa->instructions.len + i_flag]
					.mnemonics.len = i_mnemonic + 1;
				return (1);
			}
			i_mnemonic++;
		}
		item_flag = cJSON_GetObjectItemCaseSensitive(flag, JSON_FLAG_CONDITION_CODE);
		((size_t *)isa->flags.arr)[i_flag] = (size_t)cJSON_GetNumberValue(item_flag);
		i_flag++;
	}
	return (0);
}

static bool	get_registers(t_isa* isa, const cJSON* registers)
{
	isa->registers.len = cJSON_GetArraySize(registers);
	isa->registers.obj_size = sizeof(size_t);
	isa->registers.arr = malloc(isa->registers.len * isa->registers.obj_size);
	if (isa->registers.arr == NULL)
	{
		isa->registers.len = 0;
		return (1);
	}
	size_t	i = 0;
	const cJSON*	_register;
	cJSON_ArrayForEach(_register, registers)
	{
		((size_t *)isa->registers.arr)[i] = (size_t)cJSON_GetNumberValue(_register);
		i++;
	}
	return (0);
}

bool	init_isa(t_isa* isa, const cJSON* json_isa)
{
	const cJSON*	item_isa = cJSON_GetObjectItemCaseSensitive(json_isa,
		JSON_INSTRUCTION_LENGTH);
	isa->instruction_length = (size_t)cJSON_GetNumberValue(item_isa);
	item_isa = cJSON_GetObjectItemCaseSensitive(json_isa, JSON_REGISTERS);
	if (get_registers(isa, item_isa) == 1)
		return (1);
	isa->mnemonics.len = cJSON_GetArraySize(cJSON_GetObjectItemCaseSensitive(json_isa,
		JSON_INSTRUCTIONS)) + cJSON_GetArraySize(cJSON_GetObjectItemCaseSensitive(json_isa,
		JSON_FLAGS));
	isa->mnemonics.obj_size = sizeof(t_mnemonic);
	isa->mnemonics.arr = malloc(isa->mnemonics.len * isa->mnemonics.obj_size);
	if (isa->mnemonics.arr == NULL)
	{
		isa->mnemonics.len = 0;
		return (1);
	}
	item_isa = cJSON_GetObjectItemCaseSensitive(json_isa, JSON_INSTRUCTIONS);
	if (get_instructions(isa, item_isa) == 1)
		return (1);
	item_isa = cJSON_GetObjectItemCaseSensitive(json_isa, JSON_FLAGS);
	if (get_flags(isa, item_isa) == 1)
		return (1);
	return (0);
}
