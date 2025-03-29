#include <stdbool.h>
#include <stdio.h>
#include "error.h"

bool	check_arguments(int n_files)
{
	if (n_files < 1)
	{
		fprintf(stderr, "%s: %s\n", EXECUTABLE_NAME, ERROR_TOO_FEW_ARGS);
		return (1);
	}
	else if (n_files > 3)
	{
		fprintf(stderr, "%s: %s\n", EXECUTABLE_NAME, ERROR_TOO_MANY_ARGS);
		return (1);
	}
	else
		return (0);
}
