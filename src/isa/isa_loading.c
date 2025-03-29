#include <sys/stat.h>
#include "cJSON.h"
#include "files.h"
#include "error.h"

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

static void	set_instruction_data(t_isa* isa)
{
	for (size_t i_instruction = 0; i_instruction < isa->instructions.len; i_instruction++)
	{
		size_t	n_opwords = 0, bit_len = 0;
		for (size_t i_bitfield = 0;
			i_bitfield < ((t_instruction *)isa->instructions.arr)[i_instruction]
			.bitfields.len; i_bitfield++)
		{
			if (((t_bitfield *)((t_instruction *)isa->instructions.arr)[i_instruction]
				.bitfields.arr)[i_bitfield].type != CONSTANT)
				n_opwords++;
			bit_len += ((t_bitfield *)((t_instruction *)isa->instructions.arr)
				[i_instruction].bitfields.arr)[i_bitfield].len;
		}
		((t_instruction *)isa->instructions.arr)[i_instruction].n_opwords = n_opwords;
		((t_instruction *)isa->instructions.arr)[i_instruction].bit_len = bit_len;
	}
}

bool	load_isa(t_data* data)
{
	cJSON*	json = (cJSON *)parse_json_file(&data->files[INFILE_ISA]);
	if (json == NULL)
		return (1);
	if (check_isa_syntax((const cJSON *)json) == 1)
	{
		cJSON_Delete(json);
		return (1);
	}
	if (init_isa(&data->isa, (const cJSON *)json) == 1)
	{
		cJSON_Delete(json);
		fprintf(stderr, "%s: %s: %s\n",
			EXECUTABLE_NAME, FUNC_MALLOC, ERROR_FAILED_ALLOC);
		return (1);
	}
	cJSON_Delete(json);
	set_instruction_data(&data->isa);
	return (0);
}
