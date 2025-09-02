#include "data.h"
#include "files.h"
#include "error.h"

void	close_files(t_data* data)
{
	for (size_t i = 0; i < 3; i++)
		close_file(&data->files[i]);
}

bool	check_files(t_data* data)
{
	bool	error = 0;
	if (access(data->files[INFILE_PROGRAM].name, F_OK) != 0)
	{
		fprintf(stderr, "%s: %s: %s: \"%s\"\n",
			EXECUTABLE_NAME, FUNC_ACCESS, ERROR_FILE_NONEXISTANT,
			data->files[INFILE_PROGRAM].name);
		error = 1;
	}
	else if (access(data->files[INFILE_PROGRAM].name, R_OK) != 0)
	{
		fprintf(stderr, "%s: %s: %s: \"%s\"\n",
			EXECUTABLE_NAME, FUNC_ACCESS, ERROR_READ_PERM,
			data->files[INFILE_PROGRAM].name);
		error = 1;
	}
	if (access(data->files[OUTFILE_PROGRAM].name, F_OK) == 0
		&& access(data->files[OUTFILE_PROGRAM].name, W_OK) != 0)
	{
		fprintf(stderr, "%s: %s: %s: \"%s\"\n",
			EXECUTABLE_NAME, FUNC_ACCESS, ERROR_WRITE_PERM,
			data->files[OUTFILE_PROGRAM].name);
		error = 1;
	}
	if (access(data->files[INFILE_ISA].name, F_OK) != 0)
	{
		fprintf(stderr, "%s: %s: %s: \"%s\"\n",
			EXECUTABLE_NAME, FUNC_ACCESS, ERROR_FILE_NONEXISTANT,
			data->files[INFILE_ISA].name);
		error = 1;
	}
	else if (access(data->files[INFILE_ISA].name, R_OK) != 0)
	{
		fprintf(stderr, "%s: %s: %s: \"%s\"\n",
			EXECUTABLE_NAME, FUNC_ACCESS, ERROR_READ_PERM,
			data->files[INFILE_ISA].name);
		error = 1;
	}
	return (error);
}
