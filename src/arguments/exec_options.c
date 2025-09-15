#include "arguments.h"
#include "error.h"

static bool	exec_option_version(void)
{
	fprintf(stdout, "%s %s\n", EXECUTABLE_NAME, EXECUTABLE_VERSION);
	return (0);
}

static bool	exec_option_help(void)
{
	fprintf(stdout, "%s\n", EXECUTABLE_HELP);
	return (0);
}

bool	exec_options(t_option_parameter* options, bool* error)
{
	if (options[OPTION_VERSION] == YES)
	{
		*error = exec_option_version();
		return (1);
	}
	if (options[OPTION_HELP] == YES)
	{
		*error = exec_option_help();
		return (1);
	}
	return (0);
}
