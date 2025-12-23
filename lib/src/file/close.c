#include "file.h"

void	file_close(file_t *file)
{
	if (file->stream != NULL)
	{
		fclose(file->stream);
		file->stream = NULL;
	}
}
