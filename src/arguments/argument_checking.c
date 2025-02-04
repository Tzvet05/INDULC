#include <unistd.h>
#include "indulc.h"
#include "file.h"
#include "error.h"

static bool	check_files_access(int n_files, char** file_names)
{
	if (access(file_names[INFILE_PROGRAM], F_OK) != 0)
	{
		fprintf(stderr, "%s: %s: %s: \"%s\"\n", EXECUTABLE_NAME, FUNC_ACCESS,
			ERROR_FILE_NONEXISTANT, file_names[INFILE_PROGRAM]);
		return (1);
	}
	else if (access(file_names[INFILE_PROGRAM], R_OK) != 0)
	{
		fprintf(stderr, "%s: %s: %s: \"%s\"\n", EXECUTABLE_NAME, FUNC_ACCESS,
			ERROR_READ_PERM, file_names[INFILE_PROGRAM]);
		return (1);
	}
	if (n_files > 1)
	{
		if (access(file_names[OUTFILE_PROGRAM], F_OK) != 0)
		{
			fprintf(stderr, "%s: %s: %s: \"%s\"\n", EXECUTABLE_NAME, FUNC_ACCESS,
				ERROR_FILE_NONEXISTANT, file_names[OUTFILE_PROGRAM]);
			return (1);
		}
		else if (access(file_names[OUTFILE_PROGRAM], W_OK) != 0)
		{
			fprintf(stderr, "%s: %s: %s: \"%s\"\n", EXECUTABLE_NAME, FUNC_ACCESS,
				ERROR_WRITE_PERM, file_names[OUTFILE_PROGRAM]);
			return (1);
		}
	}
	if (n_files > 2)
	{
		if (access(file_names[INFILE_ISA], F_OK) != 0)
		{
			fprintf(stderr, "%s: %s: %s: \"%s\"\n", EXECUTABLE_NAME, FUNC_ACCESS,
				ERROR_FILE_NONEXISTANT, file_names[INFILE_ISA]);
			return (1);
		}
		else if (access(file_names[INFILE_ISA], R_OK) != 0)
		{
			fprintf(stderr, "%s: %s: %s: \"%s\"\n", EXECUTABLE_NAME, FUNC_ACCESS,
				ERROR_READ_PERM, file_names[INFILE_ISA]);
			return (1);
		}
	}
	return (0);
}

bool	argument_checking(int argc, char** argv)
{
	if (argc < 2)
	{
		fprintf(stderr, "%s: %s\n", EXECUTABLE_NAME, ERROR_TOO_FEW_ARGS);
		return (1);
	}
	else if (argc > 4)
	{
		fprintf(stderr, "%s: %s\n", EXECUTABLE_NAME, ERROR_TOO_MANY_ARGS);
		return (1);
	}
	else if (check_files_access(argc - 1, &argv[1]) == 1)
		return (1);
	return (0);
}
