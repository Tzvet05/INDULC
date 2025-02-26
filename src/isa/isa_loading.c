#include <sys/stat.h>
#include <string.h>
#include "cJSON.h"
#include "indulc.h"
#include "file.h"
#include "error.h"

ssize_t	get_bitfield_type(char* str)
{
	static const char* const	type_strings[] = BITFIELD_TYPES;
	t_bitfield_type	type = REGISTER;
	while (type < N_BITFIELD_TYPES && strcmp(str, type_strings[type]) != 0)
		type++;
	if (type == N_BITFIELD_TYPES)
		return (-1);
	else
		return ((ssize_t)type);
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
			.bitfields.len)
		{
			if (((t_bitfield *)((t_instruction *)isa->instructions.arr)[i_instruction]
				.bitfields.arr)[i_bitfield].type != CONSTANT)
				n_opwords++;
			i_bitfield++;
		}
		((t_instruction *)isa->instructions.arr)[i_instruction].n_opwords = n_opwords;
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
