#include "indulc.h"
#include "file.h"
#include "error.h"

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
