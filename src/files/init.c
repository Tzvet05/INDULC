#include <string.h>
#include <stdlib.h>
#include "pstr.h"
#include "file.h"
#include "data.h"
#include "error.h"

static char	*prepend(char *str, pstr_t *pre)
{
	size_t	len = strlen(str);
	char	*prepended = malloc((len + pre->len + 1) * sizeof(char));
	if (prepended == NULL)
		return (NULL);
	memcpy(prepended, pre->str, pre->len);
	memcpy(&prepended[pre->len], str, len + 1);
	return (prepended);
}

bool	init_files(data_t *data)
{
	pstr_t	input_name = file_get_name(((file_t *)data->files.arr)[INPUT_CODE].name);
	const parr_t	files = DEFAULT_FILES;
	for (size_t i = 0; i < files.len; i++)
	{
		char	*name;
		file_t	*file = &((file_t *)data->files.arr)[i],
			*default_file = &((file_t *)files.arr)[i];
		if (file->name != NULL)
		{
			if (GET_INFO(file->info, PREPEND) != 0)
				name = prepend(file->name, &input_name);
			else
				continue;
		}
		else
		{
			if (file->info == 0)
				file->info = default_file->info;
			if (default_file->name != NULL)
			{
				if (GET_INFO(file->info, PREPEND) != 0)
					name = prepend(default_file->name, &input_name);
				else
					name = strdup(default_file->name);
			}
			else
				continue;
		}
		if (name == NULL)
		{
			fprintf(stderr, "%s: %s: %s: %s: %s\n",
				EXECUTABLE_NAME, ERROR_FUNCTION, LIB_LIBC, FUNC_MALLOC,
				ERROR_ALLOC);
			return (1);
		}
		free(file->name);
		file->name = name;
	}
	return (0);
}
