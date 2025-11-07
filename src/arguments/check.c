#include "file.h"
#include "data.h"
#include "arguments.h"
#include "files.h"
#include "error.h"

bool	check_arguments(t_data *data)
{
	if (((t_file *)data->files.arr)[INFILE_CODE].name == NULL
		&& data->options[OPTION_VERSION] == PARAM_NO
		&& data->options[OPTION_HELP] == PARAM_NO)
	{
		fprintf(stderr, "%s: %s: %s\n",
			EXECUTABLE_NAME, ERROR_ARGUMENT, ERROR_ARGUMENT_TOO_FEW);
		return (1);
	}
	return (0);
}
