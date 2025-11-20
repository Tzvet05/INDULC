#include <stdint.h>
#include "cJSON.h"
#include "isa.h"
#include "error.h"
#include "nbr.h"

static bool	check_isa_registers(const cJSON *isa)
{
	bool	error = 0;
	if (cJSON_HasObjectItem(isa, JSON_REGISTERS) == 0)
	{
		fprintf(stderr, "%s: %s (\"%s\"): %s\n",
			EXECUTABLE_NAME, ERROR_JSON_SYNTAX, JSON_REGISTERS, ERROR_JSON_MISSING_ITEM);
		error = 1;
	}
	else
	{
		const cJSON	*item_isa = cJSON_GetObjectItemCaseSensitive(isa, JSON_REGISTERS);
		if (cJSON_IsArray(item_isa) == 0)
		{
			fprintf(stderr, "%s: %s (\"%s\"): %s\n",
				EXECUTABLE_NAME, ERROR_JSON_SYNTAX, JSON_REGISTERS, ERROR_JSON_NOT_ARRAY);
			error = 1;
		}
		else
		{
			size_t	i_register = 0;
			const cJSON	*_register;
			cJSON_ArrayForEach(_register, item_isa)
			{
				if (cJSON_IsObject(_register) == 0)
				{
					fprintf(stderr, "%s: %s (\"%s\" (index %zu)): %s\n",
						EXECUTABLE_NAME, ERROR_JSON_SYNTAX, JSON_REGISTERS, i_register, ERROR_JSON_NOT_OBJECT);
					error = 1;
				}
				else
				{
					if (cJSON_HasObjectItem(_register, JSON_REGISTER_MNEMONICS) == 0)
					{
						fprintf(stderr, "%s: %s (\"%s\" (index %zu): \"%s\"): %s\n",
							EXECUTABLE_NAME, ERROR_JSON_SYNTAX, JSON_REGISTERS, i_register, JSON_REGISTER_MNEMONICS, ERROR_JSON_MISSING_ITEM);
						error = 1;
					}
					else
					{
						const cJSON	*mnemonics = cJSON_GetObjectItemCaseSensitive(_register, JSON_REGISTER_MNEMONICS);
						if (cJSON_IsArray(mnemonics) == 0)
						{
							fprintf(stderr, "%s: %s (\"%s\" (index %zu): \"%s\"): %s\n",
								EXECUTABLE_NAME, ERROR_JSON_SYNTAX, JSON_REGISTERS, i_register, JSON_REGISTER_MNEMONICS, ERROR_JSON_NOT_ARRAY);
							error = 1;
						}
						else
						{
							size_t	i_mnemonic = 0;
							const cJSON	*mnemonic;
							cJSON_ArrayForEach(mnemonic, mnemonics)
							{
								if (cJSON_IsString(mnemonic) == 0)
								{
									fprintf(stderr, "%s: %s (\"%s\" (index %zu): \"%s\" (index %zu)): %s\n",
										EXECUTABLE_NAME, ERROR_JSON_SYNTAX, JSON_REGISTERS, i_register, JSON_REGISTER_MNEMONICS, i_mnemonic, ERROR_JSON_NOT_STRING);
									error = 1;
								}
							}
						}
					}
					if (cJSON_HasObjectItem(_register, JSON_REGISTER_INDEX) == 0)
					{
						fprintf(stderr, "%s: %s (\"%s\" (index %zu): \"%s\"): %s\n",
							EXECUTABLE_NAME, ERROR_JSON_SYNTAX, JSON_REGISTERS, i_register, JSON_REGISTER_INDEX, ERROR_JSON_MISSING_ITEM);
						error = 1;
					}
					else
					{
						const cJSON	*index = cJSON_GetObjectItemCaseSensitive(_register, JSON_REGISTER_INDEX);
						if (cJSON_IsNumber(index) == 0)
						{
							fprintf(stderr, "%s: %s (\"%s\" (index %zu)): %s\n",
								EXECUTABLE_NAME, ERROR_JSON_SYNTAX, JSON_REGISTERS, i_register, ERROR_JSON_NOT_NUMBER);
							error = 1;
						}
						else
						{
							double	number_value = cJSON_GetNumberValue(index);
							if ((ssize_t)number_value < 0)
							{
								fprintf(stderr, "%s: %s (\"%s\" (index %zu)): %s (must be >= 0)\n",
									EXECUTABLE_NAME, ERROR_JSON_SYNTAX, JSON_REGISTERS, i_register, ERROR_JSON_INVALID_NUMBER);
								error = 1;
							}
						}
					}
				}
				i_register++;
			}
		}
	}
	return (error);
}

static bool	check_isa_instructions(const cJSON *isa, size_t instruction_length)
{
	bool	error = 0;
	if (cJSON_HasObjectItem(isa, JSON_INSTRUCTIONS) == 0)
	{
		fprintf(stderr, "%s: %s (\"%s\"): %s\n",
			EXECUTABLE_NAME, ERROR_JSON_SYNTAX, JSON_INSTRUCTIONS, ERROR_JSON_MISSING_ITEM);
		error = 1;
	}
	else
	{
		const cJSON	*item_isa = cJSON_GetObjectItemCaseSensitive(isa, JSON_INSTRUCTIONS);
		if (cJSON_IsArray(item_isa) == 0)
		{
			fprintf(stderr, "%s: %s (\"%s\"): %s\n",
				EXECUTABLE_NAME, ERROR_JSON_SYNTAX, JSON_INSTRUCTIONS, ERROR_JSON_NOT_ARRAY);
			error = 1;
		}
		else
		{
			size_t	i_instruction = 0;
			const cJSON	*instruction;
			cJSON_ArrayForEach(instruction, item_isa)
			{
				if (cJSON_IsObject(instruction) == 0)
				{
					fprintf(stderr, "%s: %s (\"%s\" (index %zu)): %s\n",
						EXECUTABLE_NAME, ERROR_JSON_SYNTAX, JSON_INSTRUCTIONS, i_instruction, ERROR_JSON_NOT_OBJECT);
					error = 1;
				}
				else
				{
					if (cJSON_HasObjectItem(instruction, JSON_INSTRUCTION_MNEMONICS) == 0)
					{
						fprintf(stderr, "%s: %s (\"%s\" (index %zu): \"%s\"): %s\n",
							EXECUTABLE_NAME, ERROR_JSON_SYNTAX, JSON_INSTRUCTIONS, i_instruction, JSON_INSTRUCTION_MNEMONICS, ERROR_JSON_MISSING_ITEM);
						error = 1;
					}
					else
					{
						const cJSON	*mnemonics = cJSON_GetObjectItemCaseSensitive(instruction, JSON_INSTRUCTION_MNEMONICS);
						if (cJSON_IsArray(mnemonics) == 0)
						{
							fprintf(stderr, "%s: %s (\"%s\" (index %zu): \"%s\"): %s\n",
								EXECUTABLE_NAME, ERROR_JSON_SYNTAX, JSON_INSTRUCTIONS, i_instruction, JSON_INSTRUCTION_MNEMONICS, ERROR_JSON_NOT_ARRAY);
							error = 1;
						}
						else
						{
							size_t	i_mnemonic = 0;
							const cJSON	*mnemonic;
							cJSON_ArrayForEach(mnemonic, mnemonics)
							{
								if (cJSON_IsString(mnemonic) == 0)
								{
									fprintf(stderr, "%s: %s (\"%s\" (index %zu): \"%s\" (index %zu)): %s\n",
										EXECUTABLE_NAME, ERROR_JSON_SYNTAX, JSON_INSTRUCTIONS, i_instruction, JSON_INSTRUCTION_MNEMONICS, i_mnemonic,
										ERROR_JSON_NOT_STRING);
									error = 1;
								}
								i_mnemonic++;
							}
						}
					}
					if (cJSON_HasObjectItem(instruction, JSON_INSTRUCTION_BITFIELDS) == 0)
					{
						fprintf(stderr, "%s: %s (\"%s\" (index %zu): \"%s\"): %s\n",
							EXECUTABLE_NAME, ERROR_JSON_SYNTAX, JSON_INSTRUCTIONS, i_instruction, JSON_INSTRUCTION_BITFIELDS, ERROR_JSON_MISSING_ITEM);
						error = 1;
					}
					else
					{
						const cJSON	*bitfields = cJSON_GetObjectItemCaseSensitive(instruction, JSON_INSTRUCTION_BITFIELDS);
						if (cJSON_IsArray(bitfields) == 0)
						{
							fprintf(stderr, "%s: %s (\"%s\" (index %zu): \"%s\"): %s\n",
								EXECUTABLE_NAME, ERROR_JSON_SYNTAX, JSON_INSTRUCTIONS, i_instruction, JSON_INSTRUCTION_BITFIELDS, ERROR_JSON_NOT_ARRAY);
							error = 1;
						}
						else
						{
							size_t	i_bitfield = 0, sum_bitfields = 0;
							const cJSON	*bitfield;
							cJSON_ArrayForEach(bitfield, bitfields)
							{
								ssize_t	bitfield_len = BITFIELD_LEN_MAX;
								if (cJSON_IsObject(bitfield) == 0)
								{
									fprintf(stderr, "%s: %s (\"%s\" (index %zu): \"%s\" (index %zu)): %s\n",
										EXECUTABLE_NAME, ERROR_JSON_SYNTAX, JSON_INSTRUCTIONS, i_instruction, JSON_INSTRUCTION_BITFIELDS, i_bitfield,
										ERROR_JSON_NOT_OBJECT);
									error = 1;
								}
								else
								{
									if (cJSON_HasObjectItem(bitfield, JSON_INSTRUCTION_BITFIELD_LEN) == 0)
									{
										fprintf(stderr, "%s: %s (\"%s\" (index %zu): \"%s\" (index %zu): \"%s\"): %s\n",
											EXECUTABLE_NAME, ERROR_JSON_SYNTAX, JSON_INSTRUCTIONS, i_instruction, JSON_INSTRUCTION_BITFIELDS, i_bitfield,
											JSON_INSTRUCTION_BITFIELD_LEN, ERROR_JSON_MISSING_ITEM);
										error = 1;
									}
									else
									{
										const cJSON	*len = cJSON_GetObjectItemCaseSensitive(bitfield, JSON_INSTRUCTION_BITFIELD_LEN);
										if (cJSON_IsNumber(len) == 0)
										{
											fprintf(stderr, "%s: %s (\"%s\" (index %zu): \"%s\" (index %zu): \"%s\"): %s\n",
												EXECUTABLE_NAME, ERROR_JSON_SYNTAX, JSON_INSTRUCTIONS, i_instruction, JSON_INSTRUCTION_BITFIELDS, i_bitfield,
												JSON_INSTRUCTION_BITFIELD_LEN, ERROR_JSON_NOT_NUMBER);
											error = 1;
										}
										else
										{
											double	number_value = cJSON_GetNumberValue(len);
											if ((ssize_t)number_value < BITFIELD_LEN_MIN || (ssize_t)number_value > BITFIELD_LEN_MAX)
											{
												fprintf(stderr, "%s: %s (\"%s\" (index %zu): \"%s\" (index %zu): \"%s\"): %s (must be > 0 and <= 64)\n",
													EXECUTABLE_NAME, ERROR_JSON_SYNTAX, JSON_INSTRUCTIONS, i_instruction, JSON_INSTRUCTION_BITFIELDS,
													i_bitfield, JSON_INSTRUCTION_BITFIELD_LEN, ERROR_JSON_INVALID_NUMBER);
												error = 1;
											}
											else
												sum_bitfields += (size_t)number_value;
										}
									}
									if (cJSON_HasObjectItem(bitfield, JSON_INSTRUCTION_BITFIELD_TYPE) == 0)
									{
										fprintf(stderr, "%s: %s (\"%s\" (index %zu): \"%s\" (index %zu): \"%s\"): %s\n",
											EXECUTABLE_NAME, ERROR_JSON_SYNTAX, JSON_INSTRUCTIONS, i_instruction, JSON_INSTRUCTION_BITFIELDS, i_bitfield,
											JSON_INSTRUCTION_BITFIELD_TYPE, ERROR_JSON_MISSING_ITEM);
										error = 1;
									}
									else
									{
										const cJSON	*type = cJSON_GetObjectItemCaseSensitive(bitfield, JSON_INSTRUCTION_BITFIELD_TYPE);
										if (cJSON_IsString(type) == 0)
										{
											fprintf(stderr, "%s: %s (\"%s\" (index %zu): \"%s\" (index %zu): \"%s\"): %s\n",
												EXECUTABLE_NAME, ERROR_JSON_SYNTAX, JSON_INSTRUCTIONS, i_instruction, JSON_INSTRUCTION_BITFIELDS, i_bitfield,
												JSON_INSTRUCTION_BITFIELD_TYPE, ERROR_JSON_NOT_STRING);
											error = 1;
										}
										else
										{
											ssize_t	number = get_bitfield_type(cJSON_GetStringValue(type));
											if (number == -1)
											{
												fprintf(stderr, "%s: %s (\"%s\" (index %zu): \"%s\" (index %zu): \"%s\"): %s\n",
													EXECUTABLE_NAME, ERROR_JSON_SYNTAX, JSON_INSTRUCTIONS, i_instruction, JSON_INSTRUCTION_BITFIELDS,
													i_bitfield, JSON_INSTRUCTION_BITFIELD_TYPE, ERROR_JSON_BITFIELD_TYPE);
												error = 1;
											}
											else if ((t_bitfield_type)number == CONSTANT && cJSON_HasObjectItem(bitfield, JSON_INSTRUCTION_BITFIELD_VALUE) != 0)
											{
												const cJSON	*value = cJSON_GetObjectItemCaseSensitive(bitfield, JSON_INSTRUCTION_BITFIELD_VALUE);
												if (cJSON_IsNumber(value) == 0)
												{
													fprintf(stderr, "%s: %s (\"%s\" (index %zu): \"%s\" (index %zu): \"%s\"): %s\n",
														EXECUTABLE_NAME, ERROR_JSON_SYNTAX, JSON_INSTRUCTIONS, i_instruction,
														JSON_INSTRUCTION_BITFIELDS, i_bitfield, JSON_INSTRUCTION_BITFIELD_VALUE,
														ERROR_JSON_NOT_NUMBER);
													error = 1;
												}
												else
												{
													double	number_value = cJSON_GetNumberValue(value);
													if (bitfield_len >= BITFIELD_LEN_MIN && bitfield_len <= BITFIELD_LEN_MAX
														&& will_overflow_int((ssize_t)number_value, (size_t)bitfield_len) == 1)
														fprintf(stderr, "%s: %s (\"%s\" (index %zu): \"%s\" (index %zu): \"%s\"): %s\n",
															EXECUTABLE_NAME, WARNING_JSON_SYNTAX, JSON_INSTRUCTIONS, i_instruction,
															JSON_INSTRUCTION_BITFIELDS, i_bitfield, JSON_INSTRUCTION_BITFIELD_VALUE,
															WARNING_OVERFLOW);
												}
											}
										}
									}
								}
								i_bitfield++;
							}
							if (sum_bitfields > instruction_length)
							{
								fprintf(stderr, "%s: %s (\"%s\" (index %zu): \"%s\"): %s\n",
									EXECUTABLE_NAME, ERROR_JSON_SYNTAX, JSON_INSTRUCTIONS, i_instruction, JSON_INSTRUCTION_BITFIELDS, ERROR_JSON_INSTRUCTION_TOO_LONG);
								error = 1;
							}
						}
					}
				}
				i_instruction++;
			}
		}
	}
	return (error);
}

static bool	check_isa_flags(const cJSON *isa)
{
	bool	error = 0;
	if (cJSON_HasObjectItem(isa, JSON_FLAGS) == 0)
	{
		fprintf(stderr, "%s: %s (\"%s\"): %s\n",
			EXECUTABLE_NAME, ERROR_JSON_SYNTAX, JSON_FLAGS, ERROR_JSON_MISSING_ITEM);
		error = 1;
	}
	else
	{
		const cJSON	*flags = cJSON_GetObjectItemCaseSensitive(isa, JSON_FLAGS);
		if (cJSON_IsArray(flags) == 0)
		{
			fprintf(stderr, "%s: %s (\"%s\"): %s\n",
				EXECUTABLE_NAME, ERROR_JSON_SYNTAX, JSON_FLAGS, ERROR_JSON_NOT_ARRAY);
			error = 1;
		}
		else
		{
			size_t	i_flag = 0;
			const cJSON	*flag;
			cJSON_ArrayForEach(flag, flags)
			{
				if (cJSON_IsObject(flag) == 0)
				{
					fprintf(stderr, "%s: %s (\"%s\" (index %zu)): %s\n",
						EXECUTABLE_NAME, ERROR_JSON_SYNTAX, JSON_FLAGS, i_flag, ERROR_JSON_NOT_OBJECT);
					error = 1;
				}
				else
				{
					if (cJSON_HasObjectItem(flag, JSON_INSTRUCTION_MNEMONICS) == 0)
					{
						fprintf(stderr, "%s: %s (\"%s\" (index %zu): \"%s\"): %s\n",
							EXECUTABLE_NAME, ERROR_JSON_SYNTAX, JSON_FLAGS, i_flag, JSON_FLAG_MNEMONICS, ERROR_JSON_MISSING_ITEM);
						error = 1;
					}
					else
					{
						const cJSON	*mnemonics = cJSON_GetObjectItemCaseSensitive(flag, JSON_INSTRUCTION_MNEMONICS);
						if (cJSON_IsArray(mnemonics) == 0)
						{
							fprintf(stderr, "%s: %s (\"%s\" (index %zu): \"%s\"): %s\n",
								EXECUTABLE_NAME, ERROR_JSON_SYNTAX, JSON_FLAGS, i_flag, JSON_FLAG_MNEMONICS, ERROR_JSON_NOT_ARRAY);
							error = 1;
						}
						else
						{
							size_t	i_mnemonic = 0;
							const cJSON	*mnemonic;
							cJSON_ArrayForEach(mnemonic, mnemonics)
							{
								if (cJSON_IsString(mnemonic) == 0)
								{
									fprintf(stderr, "%s: %s (\"%s\" (index %zu): \"%s\" (index %zu)): %s\n",
										EXECUTABLE_NAME, ERROR_JSON_SYNTAX, JSON_FLAGS, i_flag, JSON_FLAG_MNEMONICS, i_mnemonic, ERROR_JSON_NOT_STRING);
									error = 1;
								}
								i_mnemonic++;
							}
						}
					}
					if (cJSON_HasObjectItem(flag, JSON_FLAG_CODE) == 0)
					{
						fprintf(stderr, "%s: %s (\"%s\" (index %zu): \"%s\"): %s\n",
							EXECUTABLE_NAME, ERROR_JSON_SYNTAX, JSON_FLAGS, i_flag, JSON_FLAG_CODE, ERROR_JSON_MISSING_ITEM);
						error = 1;
					}
					else
					{
						const cJSON	*code = cJSON_GetObjectItemCaseSensitive(flag, JSON_FLAG_CODE);
						if (cJSON_IsNumber(code) == 0)
						{
							fprintf(stderr, "%s: %s (\"%s\" (index %zu): \"%s\"): %s\n",
								EXECUTABLE_NAME, ERROR_JSON_SYNTAX, JSON_FLAGS, i_flag, JSON_FLAG_CODE, ERROR_JSON_NOT_NUMBER);
							error = 1;
						}
						else
						{
							double	number_value = cJSON_GetNumberValue(code);
							if ((ssize_t)number_value < 0)
							{
								fprintf(stderr, "%s: %s (\"%s\" (index %zu): \"%s\"): %s (must be >= 0)\n",
									EXECUTABLE_NAME, ERROR_JSON_SYNTAX, JSON_FLAGS, i_flag, JSON_FLAG_CODE, ERROR_JSON_INVALID_NUMBER);
								error = 1;
							}
						}
					}
				}
				i_flag++;
			}
		}
	}
	return (error);
}

bool	check_isa_syntax(const cJSON *isa)
{
	bool	error = 0;
	size_t	number = UINT64_MAX;
	if (cJSON_HasObjectItem(isa, JSON_INSTRUCTION_LENGTH) == 0)
	{
		fprintf(stderr, "%s: %s (\"%s\"): %s\n",
			EXECUTABLE_NAME, ERROR_JSON_SYNTAX, JSON_INSTRUCTION_LENGTH,
			ERROR_JSON_MISSING_ITEM);
		error = 1;
	}
	else
	{
		const cJSON	*instruction_length = cJSON_GetObjectItemCaseSensitive(isa,
			JSON_INSTRUCTION_LENGTH);
		if (cJSON_IsNumber(instruction_length) == 0)
		{
			fprintf(stderr, "%s: %s (\"%s\"): %s\n",
				EXECUTABLE_NAME, ERROR_JSON_SYNTAX, JSON_INSTRUCTION_LENGTH,
				ERROR_JSON_NOT_NUMBER);
			error = 1;
		}
		else
		{
			double	number_value = cJSON_GetNumberValue(instruction_length);
			if ((ssize_t)number_value <= 0)
			{
				fprintf(stderr, "%s: %s (\"%s\"): %s (must be > 0)\n",
					EXECUTABLE_NAME, ERROR_JSON_SYNTAX, JSON_INSTRUCTION_LENGTH,
					ERROR_JSON_INVALID_NUMBER);
				error = 1;
			}
			else if ((ssize_t)number_value > 32)
				fprintf(stderr, "%s: %s (\"%s\"): %s (should be <= 32; Json and string blueprint building will not occur as Factorio signals can only hold 32-bit values)\n",
					EXECUTABLE_NAME, WARNING_JSON_SYNTAX,
					JSON_INSTRUCTION_LENGTH, ERROR_JSON_INVALID_NUMBER);
			else
				number = (size_t)number_value;
		}
	}
	if (check_isa_registers(isa) == 1)
		error = 1;
	if (check_isa_instructions(isa, number) == 1)
		error = 1;
	if (check_isa_flags(isa) == 1)
		error = 1;
	return (error);
}
