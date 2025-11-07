#include <stdlib.h>
#include "file.h"

void	file_free(void *file)
{
	free(((t_file *)file)->name);
	if (((t_file *)file)->stream != NULL)
		fclose(((t_file *)file)->stream);
}
