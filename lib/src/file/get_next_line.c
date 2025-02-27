#include <stdlib.h>
#include "file.h"

bool	get_next_line(t_file* file, char** line_ptr)
{
	char*	line = NULL;
	size_t	null = 0;
	ssize_t	n_read = getline(&line, &null, file->stream);
	if (n_read == -1 && ferror(file->stream) == 1)
	{
		free(line);
		return (1);
	}
	else if (n_read == -1 && feof(file->stream) == 1)
	{
		free(line);
		*line_ptr = NULL;
	}
	else
		*line_ptr = line;
	return (0);
}
