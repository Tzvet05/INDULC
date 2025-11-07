#include "file.h"

void	file_close(t_file *file)
{
	if (file->stream != NULL)
	{
		fclose(file->stream);
		file->stream = NULL;
	}
}
