#include <sys/stat.h>
#include <unistd.h>
#include "file.h"
#include "data.h"
#include "error.h"

bool	check_files(t_data *data)
{
	bool	error = 0;
	for (size_t i = 0; i < data->files.len; i++)
	{
		t_file	*file = &((t_file *)data->files.arr)[i];
		if (GET_REQUIREMENT(file->info) == UNUSED)
			continue;
		if (access(file->name, F_OK) != 0)
		{
			if (GET_REQUIREMENT(file->info) == OPTIONAL)
				continue;
			fprintf(stderr, "%s: %s: \"%s\"\n",
				EXECUTABLE_NAME, ERROR_FILE_NONEXISTANT, file->name);
			error = 1;
			continue;
		}
		struct stat	file_stat;
		if (stat(file->name, &file_stat) == -1)
		{
			fprintf(stderr, "%s: %s: %s: %s: \"%s\"\n",
				EXECUTABLE_NAME, LIB_LIBC, FUNC_STAT, ERROR_FILE_STATUS,
				file->name);
			return (1);
		}
		if (S_ISREG(file_stat.st_mode) == 0)
		{
			fprintf(stderr, "%s: %s: \"%s\"\n",
				EXECUTABLE_NAME, ERROR_FILE_NONREGULAR, file->name);
			error = 1;
			continue;
		}
		if (GET_PERMISSION(file->info, READ) != 0 && access(file->name, R_OK) != 0)
		{
			fprintf(stderr, "%s: %s: \"%s\"\n",
				EXECUTABLE_NAME, ERROR_READ_PERM, file->name);
			error = 1;
		}
		if (GET_PERMISSION(file->info, WRITE) != 0 && access(file->name, W_OK) != 0)
		{
			fprintf(stderr, "%s: %s: \"%s\"\n",
				EXECUTABLE_NAME, ERROR_WRITE_PERM, file->name);
			error = 1;
		}
	}
	return (error);
}
