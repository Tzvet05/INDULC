#include <stdlib.h>
#include "file.h"

bool	get_next_line(t_file* file, char** line)
{
	*line = NULL;
	size_t	_ = 0;
	ssize_t	n_read = getline(line, &_, file->stream);
	if (n_read == -1)
	{
		free(*line);
		*line = NULL;
		if (ferror(file->stream) == 1)
			return (1);
	}
	return (0);
}
