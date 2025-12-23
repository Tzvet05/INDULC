#include <stdlib.h>
#include "file.h"

void	file_free(void *file)
{
	free(((file_t *)file)->name);
	if (((file_t *)file)->stream != NULL)
		fclose(((file_t *)file)->stream);
}
