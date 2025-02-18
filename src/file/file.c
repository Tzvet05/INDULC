#include "indulc.h"
#include "file.h"
#include "error.h"

void	close_files(t_data* data)
{
	for (size_t i = 0; i < 3; i++)
		if (data->files[i].stream != NULL)
			fclose(data->files[i].stream);
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

bool	open_file(t_file* file, char* mode)
{
	file->stream = fopen(file->name, mode);
	if (file->stream == NULL)
	{
		fprintf(stderr, "%s: %s: %s: \"%s\"\n",
			EXECUTABLE_NAME, FUNC_FOPEN, ERROR_OPEN_FILE, file->name);
		return (1);
	}
	return (0);
}
