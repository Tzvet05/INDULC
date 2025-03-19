#include "indulc.h"
#include "error.h"

void	close_files(t_data* data)
{
	for (size_t i = 0; i < 3; i++)
		close_file(&data->files[i]);
}

void	init_filenames(t_data* data, char** file_names)
{
	data->files[INFILE_PROGRAM].name = file_names[INFILE_PROGRAM];
	if (file_names[OUTFILE_PROGRAM] != NULL)
	{
		data->files[OUTFILE_PROGRAM].name = file_names[OUTFILE_PROGRAM];
		if (file_names[INFILE_ISA] != NULL)
			data->files[INFILE_ISA].name = file_names[INFILE_ISA];
		else
			data->files[INFILE_ISA].name = DEFAULT_INFILE_ISA;
	}
	else
	{
		data->files[OUTFILE_PROGRAM].name = DEFAULT_OUTFILE_PROGRAM;
		data->files[INFILE_ISA].name = DEFAULT_INFILE_ISA;
	}
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
