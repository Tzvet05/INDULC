#include <string.h>
#include "pstr.h"

t_pstr	file_get_name(char *path)
{
	t_pstr	file = (t_pstr){.len = strlen(path), .str = path};
	char	*ptr = strrchr(file.str, '/');
	if (ptr != NULL)
	{
		ptr++;
		file.len -= (size_t)(ptr - file.str);
		file.str = ptr;
	}
	ptr = strrchr(file.str, '.');
	if (ptr != NULL)
		file.len = (size_t)(ptr - file.str);
	return (file);
}
