#include "file.h"

bool	file_open(file_t *file, char *mode)
{
	file->stream = fopen(file->name, mode);
	return (file->stream == NULL);
}
