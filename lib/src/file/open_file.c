#include "file.h"

bool	open_file(t_file* file, char* mode)
{
	file->stream = fopen(file->name, mode);
	return (file->stream == NULL);
}
