#include "indulc.h"
#include "file.h"
#include "error.h"

bool	open_file(t_file* file, char* mode)
{
	file->stream = fopen(file->name, mode);
	if (file->stream == NULL)
	{
		fprintf(stderr, "%s: %s: %s: \"%s\"\n",
			EXECUTABLE_NAME, FUNC_FOPEN, ERROR_OPEN_FILE, file->name);
		return (1);
	}
	return (0);
}
