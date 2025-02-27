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
