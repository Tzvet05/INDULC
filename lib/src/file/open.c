#include "file.h"

bool	file_open(t_file *file, char *mode)
{
	file->stream = fopen(file->name, mode);
	return (file->stream == NULL);
}
