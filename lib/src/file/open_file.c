#include "file.h"

bool	open_file(t_file* file, char* mode)
{
	file->stream = fopen(file->name, mode);
	if (file->stream == NULL)
		return (1);
	return (0);
}
