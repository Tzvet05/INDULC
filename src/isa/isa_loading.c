#include <sys/stat.h>
#include <string.h>
#include "cJSON.h"
#include "indulc.h"
#include "file.h"
#include "error.h"

static ssize_t	get_bitfield_type(char* str)
{
	static const char* const	type_strings[] = BITFIELD_TYPES;
	t_bitfield_type	type = OPCODE;
	while (type < N_BITFIELD_TYPES && strcmp(str, type_strings[type]) != 0)
		type++;
	if (type == N_BITFIELD_TYPES)
		return (-1);
	else
		return ((ssize_t)type);
}

static bool	check_isa_syntax(const cJSON* isa)
{
	const cJSON*	item_isa = cJSON_GetObjectItemCaseSensitive(isa,
		JSON_ISA_KEY_NB_REGISTERS);
	if (cJSON_IsNumber(item_isa) == 0)
	{
		fprintf(stderr, "%s: %s: %s\n",
			EXECUTABLE_NAME, ERROR_JSON_SYNTAX, ERROR_JSON_NOT_NUMBER);
		return (1);
	}
	item_isa = cJSON_GetObjectItemCaseSensitive(isa, JSON_ISA_KEY_INSTRUCTIONS);
	if (cJSON_IsArray(item_isa) == 0)
	{
		fprintf(stderr, "%s: %s: %s\n",
			EXECUTABLE_NAME, ERROR_JSON_SYNTAX, ERROR_JSON_NOT_ARRAY);
		return (1);
	}
	const cJSON*	instruction;
	cJSON_ArrayForEach(instruction, item_isa)
	{
		const cJSON*	item_instruction = cJSON_GetObjectItemCaseSensitive(instruction,
			JSON_ISA_KEY_INSTRUCTION_MNEMONICS);
		if (cJSON_IsArray(item_instruction) == 0)
		{
			fprintf(stderr, "%s: %s: %s\n",
				EXECUTABLE_NAME, ERROR_JSON_SYNTAX, ERROR_JSON_NOT_ARRAY);
			return (1);
		}
		const cJSON*	mnemonic;
		cJSON_ArrayForEach(mnemonic, item_instruction)
		{
			if (cJSON_IsString(mnemonic) == 0)
			{
				fprintf(stderr, "%s: %s: %s\n",
					EXECUTABLE_NAME, ERROR_JSON_SYNTAX, ERROR_JSON_NOT_STRING);
				return (1);
			}
		}
		item_instruction = cJSON_GetObjectItemCaseSensitive(instruction,
			JSON_ISA_KEY_INSTRUCTION_OPCODE);
		if (cJSON_IsNumber(item_instruction) == 0)
		{
			fprintf(stderr, "%s: %s: %s\n",
				EXECUTABLE_NAME, ERROR_JSON_SYNTAX, ERROR_JSON_NOT_NUMBER);
			return (1);
		}
		item_instruction = cJSON_GetObjectItemCaseSensitive(instruction,
			JSON_ISA_KEY_INSTRUCTION_BITFIELDS);
		if (cJSON_IsArray(item_instruction) == 0)
		{
			fprintf(stderr, "%s: %s: %s\n",
				EXECUTABLE_NAME, ERROR_JSON_SYNTAX, ERROR_JSON_NOT_ARRAY);
			return (1);
		}
		const cJSON*	bitfield;
		cJSON_ArrayForEach(bitfield, item_instruction)
		{
			const cJSON*	item_format = cJSON_GetObjectItemCaseSensitive(bitfield,
				JSON_ISA_KEY_INSTRUCTION_BITFIELD_LEN);
			if (cJSON_IsNumber(item_format) == 0)
			{
				fprintf(stderr, "%s: %s: %s\n",
					EXECUTABLE_NAME, ERROR_JSON_SYNTAX, ERROR_JSON_NOT_NUMBER);
				return (1);
			}
			item_format = cJSON_GetObjectItemCaseSensitive(bitfield,
				JSON_ISA_KEY_INSTRUCTION_BITFIELD_TYPE);
			if (cJSON_IsString(item_format) == 0)
			{
				fprintf(stderr, "%s: %s: %s\n",
					EXECUTABLE_NAME, ERROR_JSON_SYNTAX, ERROR_JSON_NOT_STRING);
				return (1);
			}
			if (get_bitfield_type(cJSON_GetStringValue(item_format)) == -1)
			{
				fprintf(stderr, "%s: %s: %s\n",
					EXECUTABLE_NAME, ERROR_JSON_SYNTAX,
					ERROR_JSON_INVALID_BITFIELD_TYPE);
				return (1);
			}
		}
	}
	item_isa = cJSON_GetObjectItemCaseSensitive(isa, JSON_ISA_KEY_FLAGS);
	if (cJSON_IsArray(item_isa) == 0)
	{
		fprintf(stderr, "%s: %s: %s\n",
			EXECUTABLE_NAME, ERROR_JSON_SYNTAX, ERROR_JSON_NOT_ARRAY);
		return (1);
	}
	const cJSON*	flag;
	cJSON_ArrayForEach(flag, item_isa)
	{
		const cJSON*	item_flag = cJSON_GetObjectItemCaseSensitive(flag,
			JSON_ISA_KEY_FLAG_MNEMONICS);
		if (cJSON_IsArray(item_flag) == 0)
		{
			fprintf(stderr, "%s: %s: %s\n",
				EXECUTABLE_NAME, ERROR_JSON_SYNTAX, ERROR_JSON_NOT_ARRAY);
			return (1);
		}
		const cJSON*	mnemonic;
		cJSON_ArrayForEach(mnemonic, item_flag)
		{
			if (cJSON_IsString(mnemonic) == 0)
			{
				fprintf(stderr, "%s: %s: %s\n",
					EXECUTABLE_NAME, ERROR_JSON_SYNTAX, ERROR_JSON_NOT_STRING);
				return (1);
			}
		}
		item_flag = cJSON_GetObjectItemCaseSensitive(flag,
			JSON_ISA_KEY_FLAG_CONDITION_CODE);
		if (cJSON_IsNumber(item_flag) == 0)
		{
			fprintf(stderr, "%s: %s: %s\n",
				EXECUTABLE_NAME, ERROR_JSON_SYNTAX, ERROR_JSON_NOT_NUMBER);
			return (1);
		}
	}
	return (0);
}

static bool	get_instructions(t_isa* isa, const cJSON* instructions)
{
	isa->instructions.len = cJSON_GetArraySize(instructions);
	isa->instructions.arr = malloc(isa->instructions.len * sizeof(t_instruction));
	if (isa->instructions.arr == NULL)
		return (1);
	size_t	i_instruction = 0;
	const cJSON*	instruction;
	cJSON_ArrayForEach(instruction, instructions)
	{
		((t_mnemonic *)isa->mnemonics.arr)[i_instruction].compilation_target
			= (void *)&((t_instruction *)isa->instructions.arr)[i_instruction];
		((t_mnemonic *)isa->mnemonics.arr)[i_instruction].type = INSTRUCTION;
		const cJSON*	item_instruction = cJSON_GetObjectItemCaseSensitive(instruction,
			JSON_ISA_KEY_INSTRUCTION_MNEMONICS);
		((t_mnemonic *)isa->mnemonics.arr)[i_instruction].mnemonics.len
			= cJSON_GetArraySize(item_instruction);
		((t_mnemonic *)isa->mnemonics.arr)[i_instruction].mnemonics.arr
			= malloc(((t_mnemonic *)isa->mnemonics.arr)[i_instruction].mnemonics.len
			* sizeof(char *));
		if (((t_mnemonic *)isa->mnemonics.arr)[i_instruction].mnemonics.arr == NULL)
			return (1);
		size_t	i_mnemonic = 0;
		const cJSON*	mnemonic;
		cJSON_ArrayForEach(mnemonic, item_instruction)
		{
			((char **)((t_mnemonic *)isa->mnemonics.arr)[i_instruction]
				.mnemonics.arr)[i_mnemonic]
				= strdup(cJSON_GetStringValue(mnemonic));
			if (((char **)((t_mnemonic *)isa->mnemonics.arr)[i_instruction]
				.mnemonics.arr)[i_mnemonic] == NULL)
				return (1);
			i_mnemonic++;
		}
		item_instruction = cJSON_GetObjectItemCaseSensitive(instruction,
			JSON_ISA_KEY_INSTRUCTION_OPCODE);
		((t_instruction *)isa->instructions.arr)[i_instruction].opcode
			= (size_t)cJSON_GetNumberValue(item_instruction);
		item_instruction = cJSON_GetObjectItemCaseSensitive(instruction,
			JSON_ISA_KEY_INSTRUCTION_BITFIELDS);
		((t_instruction *)isa->instructions.arr)[i_instruction].format.bitfields.len
			= cJSON_GetArraySize(item_instruction);
		((t_instruction *)isa->instructions.arr)[i_instruction].format.bitfields.arr
			= malloc(((t_instruction *)isa->instructions.arr)[i_instruction]
			.format.bitfields.len * sizeof(t_bitfield));
		if (((t_instruction *)isa->instructions.arr)[i_instruction]
			.format.bitfields.arr == NULL)
			return (1);
		size_t	i_bitfield = 0;
		const cJSON*	bitfield;
		cJSON_ArrayForEach(bitfield, item_instruction)
		{
			const cJSON*	item_bitfield = cJSON_GetObjectItemCaseSensitive(bitfield,
				JSON_ISA_KEY_INSTRUCTION_BITFIELD_LEN);
			((t_bitfield *)((t_instruction *)isa->instructions.arr)[i_instruction]
				.format.bitfields.arr)[i_bitfield].len
				= (size_t)cJSON_GetNumberValue(item_bitfield);
			item_bitfield = cJSON_GetObjectItemCaseSensitive(bitfield,
				JSON_ISA_KEY_INSTRUCTION_BITFIELD_TYPE);
			((t_bitfield *)((t_instruction *)isa->instructions.arr)[i_instruction]
				.format.bitfields.arr)[i_bitfield].type = (t_bitfield_type)
				get_bitfield_type(cJSON_GetStringValue(item_bitfield));
			i_bitfield++;
		}
		i_instruction++;
	}
	return (0);
}

static bool	get_flags(t_isa* isa, const cJSON* flags)
{
	isa->flags.len = cJSON_GetArraySize(flags);
	isa->flags.arr = malloc(isa->flags.len * sizeof(size_t));
	if (isa->flags.arr == NULL)
		return (1);
	size_t	i_flag = 0;
	const cJSON*	flag;
	cJSON_ArrayForEach(flag, flags)
	{
		((t_mnemonic *)isa->mnemonics.arr)[isa->instructions.len
			+ i_flag].compilation_target = (void *)&((size_t *)isa->flags.arr)[i_flag];
		((t_mnemonic *)isa->mnemonics.arr)[isa->instructions.len + i_flag].type = FLAG;
		const cJSON*	item_flag = cJSON_GetObjectItemCaseSensitive(flag,
			JSON_ISA_KEY_FLAG_MNEMONICS);
		((t_mnemonic *)isa->mnemonics.arr)[isa->instructions.len + i_flag].mnemonics.len
			= cJSON_GetArraySize(item_flag);
		((t_mnemonic *)isa->mnemonics.arr)[isa->instructions.len + i_flag].mnemonics.arr
			= malloc(((t_mnemonic *)isa->mnemonics.arr)[isa->instructions.len
			+ i_flag].mnemonics.len * sizeof(char *));
		if (((t_mnemonic *)isa->mnemonics.arr)[isa->instructions.len
			+ i_flag].mnemonics.arr == NULL)
			return (1);
		size_t	i_mnemonic = 0;
		const cJSON*	mnemonic;
		cJSON_ArrayForEach(mnemonic, item_flag)
		{
			((char **)((t_mnemonic *)isa->mnemonics.arr)[isa->instructions.len
				+ i_flag].mnemonics.arr)[i_mnemonic]
				= strdup(cJSON_GetStringValue(mnemonic));
			if (((char **)((t_mnemonic *)isa->mnemonics.arr)[isa->instructions.len
				+ i_flag].mnemonics.arr)[i_mnemonic] == NULL)
				return (1);
			i_mnemonic++;
		}
		item_flag = cJSON_GetObjectItemCaseSensitive(flag,
			JSON_ISA_KEY_FLAG_CONDITION_CODE);
		((size_t *)isa->flags.arr)[i_flag] = (size_t)cJSON_GetNumberValue(item_flag);
		i_flag++;
	}
	return (0);
}

static bool	init_isa(t_isa* isa, const cJSON* json_isa)
{
	const cJSON*	item_isa = cJSON_GetObjectItemCaseSensitive(json_isa,
		JSON_ISA_KEY_NB_REGISTERS);
	isa->n_registers = (size_t)cJSON_GetNumberValue(item_isa);
	isa->mnemonics.len = cJSON_GetArraySize(cJSON_GetObjectItemCaseSensitive(json_isa,
		JSON_ISA_KEY_INSTRUCTIONS))
		+ cJSON_GetArraySize(cJSON_GetObjectItemCaseSensitive(json_isa,
		JSON_ISA_KEY_FLAGS));
	isa->mnemonics.arr = malloc(isa->mnemonics.len * sizeof(t_mnemonic));
	if (isa->mnemonics.arr == NULL)
		return (1);
	item_isa = cJSON_GetObjectItemCaseSensitive(json_isa, JSON_ISA_KEY_INSTRUCTIONS);
	if (get_instructions(isa, item_isa) == 1)
		return (1);
	item_isa = cJSON_GetObjectItemCaseSensitive(json_isa, JSON_ISA_KEY_FLAGS);
	if (get_flags(isa, item_isa) == 1)
		return (1);
	return (0);
}

static const cJSON*	parse_json_file(t_file* file)
{
	struct stat	file_status;
	if (stat(file->name, &file_status) != 0)
	{
		fprintf(stderr, "%s: %s: %s: \"%s\"\n",
			EXECUTABLE_NAME, FUNC_STAT, ERROR_FILE_STATUS, file->name);
		return (NULL);
	}
	char*	buffer = malloc((file_status.st_size + 1) * sizeof(char));
	if (buffer == NULL)
	{
		fprintf(stderr, "%s: %s: %s\n",
			EXECUTABLE_NAME, FUNC_MALLOC, ERROR_FAILED_ALLOC);
		return (NULL);
	}
	buffer[file_status.st_size] = '\0';
	fread(buffer, 1, file_status.st_size, file->stream);
	if (ferror(file->stream) != 0)
	{
		fprintf(stderr, "%s: %s: %s: \"%s\"\n",
			EXECUTABLE_NAME, FUNC_FREAD, ERROR_READ_FILE, file->name);
		return (NULL);
	}
	cJSON*	json = cJSON_Parse(buffer);
	if (json == NULL)
	{
		fprintf(stderr, "%s: %s: %s: %s: \"%s\": ",
			EXECUTABLE_NAME, ERROR_CJSON_LIB, FUNC_CJSON_PARSE, ERROR_CJSON_PARSE,
			file->name);
		const char*	error = cJSON_GetErrorPtr();
		if (error != NULL)
			fprintf(stderr, "error is located at: %s\n", error);
		else
			fprintf(stderr, "location of error is unrecoverable\n");
		free(buffer);
		cJSON_Delete(json);
		return (NULL);
	}
	free(buffer);
	return ((const cJSON *)json);
}

static void	set_opwords(t_isa* isa)
{
	size_t	i_instruction = 0;
	while (i_instruction < isa->instructions.len)
	{
		size_t	i_bitfield = 0, n_opwords = 0;
		while (i_bitfield < ((t_instruction *)isa->instructions.arr)[i_instruction]
			.format.bitfields.len)
		{
			if (((t_bitfield *)((t_instruction *)isa->instructions.arr)[i_instruction]
				.format.bitfields.arr)[i_bitfield].type != UNUSED)
				n_opwords++;
			i_bitfield++;
		}
		((t_instruction *)isa->instructions.arr)[i_instruction].format.n_opwords
			= n_opwords;
		i_instruction++;
	}
}

bool	isa_loading(t_data* data)
{
	cJSON*	json = (cJSON *)parse_json_file(&data->files[INFILE_ISA]);
	if (json == NULL)
		return (1);
	else if (check_isa_syntax((const cJSON *)json) == 1)
	{
		cJSON_Delete(json);
		return (1);
	}
	else if (init_isa(&data->isa, (const cJSON *)json) == 1)
	{
		cJSON_Delete(json);
		fprintf(stderr, "%s: %s: %s\n",
			EXECUTABLE_NAME, FUNC_MALLOC, ERROR_FAILED_ALLOC);
		return (1);
	}
	cJSON_Delete(json);
	set_opwords(&data->isa);
	return (0);
}
