#include "indulc.h"
#include "file.h"
#include "error.h"

bool	file_opening(t_data* data, char** file_names)
{
	data->files.len = 3;
	data->files.arr = malloc(data->files.len * sizeof(t_file));
	if (data->files.arr == NULL)
	{
		data->files.len = 0;
		fprintf(stderr, "%s: %s: %s\n", EXECUTABLE_NAME, FUNC_MALLOC, ERROR_FAILED_ALLOC);
		return (1);
	}
	((t_file *)data->files.arr)[INFILE_PROGRAM].name = file_names[INFILE_PROGRAM];
	if (file_names[OUTFILE_PROGRAM] != NULL)
	{
		((t_file *)data->files.arr)[OUTFILE_PROGRAM].name = file_names[OUTFILE_PROGRAM];
		if (file_names[INFILE_ISA] != NULL)
			((t_file *)data->files.arr)[INFILE_ISA].name = file_names[INFILE_ISA];
		else
			((t_file *)data->files.arr)[INFILE_ISA].name = DEFAULT_INFILE_ISA;
	}
	else
	{
		((t_file *)data->files.arr)[OUTFILE_PROGRAM].name = DEFAULT_OUTFILE_PROGRAM;
		((t_file *)data->files.arr)[INFILE_ISA].name = DEFAULT_INFILE_ISA;
	}
	((t_file *)data->files.arr)[INFILE_PROGRAM].stream =
		fopen(((t_file *)data->files.arr)[INFILE_PROGRAM].name, "r");
	((t_file *)data->files.arr)[OUTFILE_PROGRAM].stream =
		fopen(((t_file *)data->files.arr)[OUTFILE_PROGRAM].name, "w");
	((t_file *)data->files.arr)[INFILE_ISA].stream =
		fopen(((t_file *)data->files.arr)[INFILE_ISA].name, "r");
	if (((t_file *)data->files.arr)[INFILE_PROGRAM].stream == NULL)
	{
		fprintf(stderr, "%s: %s: %s: \"%s\"\n", EXECUTABLE_NAME, FUNC_FOPEN,
			ERROR_OPEN_FILE, ((t_file *)data->files.arr)[INFILE_PROGRAM].name);
		return (1);
	}
	else if (((t_file *)data->files.arr)[OUTFILE_PROGRAM].stream == NULL)
	{
		fprintf(stderr, "%s: %s: %s: \"%s\"\n", EXECUTABLE_NAME, FUNC_FOPEN,
			ERROR_OPEN_FILE, ((t_file *)data->files.arr)[OUTFILE_PROGRAM].name);
		return (1);
	}
	else if (((t_file *)data->files.arr)[INFILE_ISA].stream == NULL)
	{
		fprintf(stderr, "%s: %s: %s: \"%s\"\n", EXECUTABLE_NAME, FUNC_FOPEN,
			ERROR_OPEN_FILE, ((t_file *)data->files.arr)[INFILE_ISA].name);
		return (1);
	}
	return (0);
}
