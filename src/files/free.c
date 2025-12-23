#include "parr.h"
#include "file.h"

void	free_files(parr_t *files)
{
	for (size_t i = 0; i < files->len; i++)
		file_free(&((file_t *)files->arr)[i]);
}
