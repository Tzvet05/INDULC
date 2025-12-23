#include <sys/stat.h>
#include <stdlib.h>
#include "cJSON.h"
#include "file.h"
#include "error.h"

const cJSON	*parse_json_file(file_t *file)
{
	struct stat	file_status;
	if (stat(file->name, &file_status) != 0)
	{
		fprintf(stderr, "%s: %s: %s: %s: %s: \"%s\"\n",
			EXECUTABLE_NAME, ERROR_FUNCTION, LIB_LIBC, FUNC_STAT, ERROR_FILE_STATUS,
			file->name);
		return (NULL);
	}
	char	*buffer = malloc(((size_t)file_status.st_size + 1) * sizeof(char));
	if (buffer == NULL)
	{
		fprintf(stderr, "%s: %s: %s: %s: %s\n",
			EXECUTABLE_NAME, ERROR_FUNCTION, LIB_LIBC, FUNC_MALLOC, ERROR_ALLOC);
		return (NULL);
	}
	buffer[file_status.st_size] = '\0';
	fread(buffer, 1, (size_t)file_status.st_size, file->stream);
	if (ferror(file->stream) != 0)
	{
		fprintf(stderr, "%s: %s: %s: %s: %s: \"%s\"\n",
			EXECUTABLE_NAME, ERROR_FUNCTION, LIB_LIBC, FUNC_FREAD, ERROR_READ_FILE,
			file->name);
		free(buffer);
		return (NULL);
	}
	const cJSON	*json = cJSON_Parse(buffer);
	if (json == NULL)
	{
		fprintf(stderr, "%s: %s: %s: %s: %s: \"%s\": ",
			EXECUTABLE_NAME, ERROR_FUNCTION, LIB_CJSON, FUNC_CJSON_PARSE,
			ERROR_CJSON_PARSE, file->name);
		const char	*error = cJSON_GetErrorPtr();
		if (error != NULL)
			fprintf(stderr, "%s", error);
		else
			fprintf(stderr, "error location is unrecoverable\n");
		free(buffer);
		return (NULL);
	}
	free(buffer);
	return (json);
}
