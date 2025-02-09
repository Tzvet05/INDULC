#include "indulc.h"
#include "file.h"
#include "error.h"

bool	input_file_opening(t_data* data)
{
	data->files[INFILE_PROGRAM].stream = fopen(data->files[INFILE_PROGRAM].name, "r");
	data->files[INFILE_ISA].stream = fopen(data->files[INFILE_ISA].name, "r");
	if (data->files[INFILE_PROGRAM].stream == NULL)
	{
		fprintf(stderr, "%s: %s: %s: \"%s\"\n", EXECUTABLE_NAME, FUNC_FOPEN,
			ERROR_OPEN_FILE, data->files[INFILE_PROGRAM].name);
		return (1);
	}
	else if (data->files[INFILE_ISA].stream == NULL)
	{
		fprintf(stderr, "%s: %s: %s: \"%s\"\n", EXECUTABLE_NAME, FUNC_FOPEN,
			ERROR_OPEN_FILE, data->files[INFILE_ISA].name);
		return (1);
	}
	return (0);
}

bool	output_file_opening(t_data* data)
{
	data->files[OUTFILE_PROGRAM].stream = fopen(data->files[OUTFILE_PROGRAM].name, "w");
	if (data->files[OUTFILE_PROGRAM].stream == NULL)
	{
		fprintf(stderr, "%s: %s: %s: \"%s\"\n", EXECUTABLE_NAME, FUNC_FOPEN,
			ERROR_OPEN_FILE, data->files[OUTFILE_PROGRAM].name);
		return (1);
	}
	return (0);
}
