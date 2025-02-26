#include "file.h"

void	close_file(t_file* file)
{
	if (file->stream != NULL)
		fclose(file->stream);
}
