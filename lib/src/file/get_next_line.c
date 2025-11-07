#include <stdlib.h>
#include "file.h"

bool	file_get_next_line(t_file *file, char **line)
{
	*line = NULL;
	size_t	_ = 0;
	if (getline(line, &_, file->stream) == -1)
	{
		free(*line);
		*line = NULL;
		if (ferror(file->stream) == 1)
			return (1);
	}
	return (0);
}
