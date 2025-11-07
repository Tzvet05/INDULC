#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "data.h"
#include "files.h"

bool	alloc_files(t_data *data)
{
	const t_parr	files = DEFAULT_FILES;
	data->files.len = files.len;
	data->files.obj_size = files.obj_size;
	data->files.arr = calloc(data->files.len, data->files.obj_size);
	if (data->files.arr == NULL)
	{
		data->files.len = 0;
		return (1);
	}
	return (0);
}

bool	init_files(t_data *data)
{
	const t_parr	files = DEFAULT_FILES;
	for (size_t i = 0; i < files.len; i++)
	{
		if (((t_file *)data->files.arr)[i].info == 0)
		{
			if (((t_file *)data->files.arr)[i].name == NULL
				&& ((t_file *)files.arr)[i].name != NULL)
			{
				((t_file *)data->files.arr)[i].name
					= strdup(((t_file *)files.arr)[i].name);
				if (((t_file *)data->files.arr)[i].name == NULL)
					return (1);
			}
			((t_file *)data->files.arr)[i].info = ((t_file *)files.arr)[i].info;
		}
	}
	return (0);
}
