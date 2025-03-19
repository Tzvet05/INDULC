#include <stdlib.h>
#include "file.h"

bool	get_next_line(t_file* file, char** line)
{
	size_t	_ = 0;
	ssize_t	n_read = getline(line, &_, file->stream);
	if (n_read == -1 && ferror(file->stream) == 1)
	{
		free(*line);
		*line = NULL;
		return (1);
	}
	else if (n_read == -1 && feof(file->stream) == 1)
	{
		free(*line);
		*line = NULL;
	}
	return (0);
}
