#include "arguments.h"
#include "error.h"

bool	exec_options(uint8_t options)
{
	if (options & OPTION_VERSION)
	{
		fprintf(stdout, "%s %s\n", EXECUTABLE_NAME, EXECUTABLE_VERSION);
		return (1);
	}
	else if (options & OPTION_HELP)
	{
		fprintf(stdout, "%s\n", EXECUTABLE_HELP);
		return (1);
	}
	return (0);
}
