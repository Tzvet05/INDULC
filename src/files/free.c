#include "parr.h"
#include "file.h"

void	free_files(t_parr *files)
{
	for (size_t i = 0; i < files->len; i++)
		file_free(&((t_file *)files->arr)[i]);
}
