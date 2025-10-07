#include "data.h"
#include "arguments.h"
#include "files.h"
#include "error.h"

bool	check_arguments(t_data* data)
{
	if (((t_file *)data->files.arr)[INFILE_PROGRAM].name == NULL
		&& data->options[OPTION_VERSION] == NO && data->options[OPTION_HELP] == NO)
	{
		fprintf(stderr, "%s: %s: %s\n",
			EXECUTABLE_NAME, ERROR_ARGUMENT, ERROR_ARGUMENT_TOO_FEW);
		return (1);
	}
	return (0);
}
