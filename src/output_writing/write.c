#include <stdlib.h>
#include <string.h>
#include "cJSON.h"
#include "file.h"
#include "arguments.h"
#include "error.h"

bool	write_machine_code(t_parr *machine_code, t_file *file, t_option_parameter *options)
{
	if (file_open(file, FOPEN_WRITE_MODE) == 1)
	{
		fprintf(stderr, "%s: %s: %s: %s: \"%s\"\n",
			EXECUTABLE_NAME, LIB_LIBC, FUNC_FOPEN, ERROR_OPEN_FILE, file->name);
		return (1);
	}
	if (options[OPTION_MACHINE_CODE_OUTPUT] == PARAM_BIN)
		fwrite(machine_code->arr, machine_code->obj_size, machine_code->len, file->stream);
	else
	{
		size_t	len_instr = machine_code->obj_size * 8 + machine_code->obj_size,
			len = len_instr * machine_code->len;
		char	*buffer = malloc(len * sizeof(char));
		if (buffer == NULL)
		{
			fprintf(stderr, "%s: %s: %s: %s\n",
				EXECUTABLE_NAME, LIB_LIBC, FUNC_MALLOC, ERROR_FAILED_ALLOC);
			file_close(file);
			return (1);
		}
		for (size_t i_instr = 0; i_instr < machine_code->len; i_instr++)
		{
			for (size_t i_byte = 0; i_byte < machine_code->obj_size; i_byte++)
			{
				uint8_t	byte = ((uint8_t *)machine_code->arr)[i_instr
					* machine_code->obj_size + i_byte];
				for (size_t i_bit = 0; i_bit < 8; i_bit++)
				{
					buffer[i_instr * len_instr + i_byte * (8 + 1)
						+ ((8 - 1) - i_bit)] = (byte & 1) + '0';
					byte >>= 1;
				}
				char	end;
				if (i_byte + 1 == machine_code->obj_size)
					end = '\n';
				else
					end = ' ';
				buffer[i_instr * len_instr + i_byte * (8 + 1) + 8] = end;
			}
		}
		fwrite(buffer, sizeof(*buffer), len, file->stream);
		free(buffer);
	}
	if (ferror(file->stream) != 0)
	{
		fprintf(stderr, "%s: %s: %s: %s: \"%s\"\n",
			EXECUTABLE_NAME, LIB_LIBC, FUNC_FWRITE, ERROR_WRITE_FILE, file->name);
		file_close(file);
		return (1);
	}
	file_close(file);
	return (0);
}

bool	write_json(const cJSON *json, t_file *file, t_option_parameter *options)
{
	const char	*str;
	if (options[OPTION_JSON_OUTPUT] == PARAM_FORMAT)
	{
		str = cJSON_Print(json);
		if (str == NULL)
		{
			fprintf(stderr, "%s: %s: %s: %s\n",
				EXECUTABLE_NAME, LIB_CJSON, FUNC_CJSON_PRINT, ERROR_CJSON_PRINT);
			return (1);
		}
	}
	else
	{
		str = cJSON_PrintUnformatted(json);
		if (str == NULL)
		{
			fprintf(stderr, "%s: %s: %s: %s\n",
				EXECUTABLE_NAME, LIB_CJSON, FUNC_CJSON_PRINT,
				ERROR_CJSON_PRINT_UNFORMATTED);
			return (1);
		}
	}
	if (file_open(file, FOPEN_WRITE_MODE) == 1)
	{
		fprintf(stderr, "%s: %s: %s: %s: \"%s\"\n",
			EXECUTABLE_NAME, LIB_LIBC, FUNC_FOPEN, ERROR_OPEN_FILE, file->name);
		free((void *)str);
		return (1);
	}
	fwrite(str, sizeof(*str), strlen(str), file->stream);
	free((void *)str);
	if (ferror(file->stream) != 0)
	{
		fprintf(stderr, "%s: %s: %s: %s: \"%s\"\n",
			EXECUTABLE_NAME, LIB_LIBC, FUNC_FWRITE, ERROR_WRITE_FILE, file->name);
		file_close(file);
		return (1);
	}
	file_close(file);
	return (0);
}

bool	write_string(t_parr *string, t_file *file, t_option_parameter *options)
{
	if (options[OPTION_STRING_OUTPUT] == PARAM_FILE
		|| options[OPTION_STRING_OUTPUT] == PARAM_ALL)
	{
		if (file_open(file, FOPEN_WRITE_MODE) == 1)
		{
			fprintf(stderr, "%s: %s: %s: %s: \"%s\"\n",
				EXECUTABLE_NAME, LIB_LIBC, FUNC_FOPEN, ERROR_OPEN_FILE, file->name);
			return (1);
		}
		fwrite(string->arr, string->obj_size, string->len, file->stream);
		if (ferror(file->stream) != 0)
		{
			fprintf(stderr, "%s: %s: %s: %s: \"%s\"\n",
				EXECUTABLE_NAME, LIB_LIBC, FUNC_FWRITE, ERROR_WRITE_FILE,
				file->name);
			file_close(file);
			return (1);
		}
		file_close(file);
	}
	if (options[OPTION_STRING_OUTPUT] == PARAM_TERMINAL
		|| options[OPTION_STRING_OUTPUT] == PARAM_ALL)
	{
		fprintf(stdout, "%.*s\n", (int32_t)(string->len * string->obj_size),
			(char *)string->arr);
		if (ferror(stdout) != 0)
		{
			fprintf(stderr, "%s: %s: %s: %s\n",
				EXECUTABLE_NAME, LIB_LIBC, FUNC_FWRITE, ERROR_WRITE_STDOUT);
			return (1);
		}
	}
	return (0);
}
