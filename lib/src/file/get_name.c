#include <string.h>
#include "pstr.h"

pstr_t	file_get_name(char *path)
{
	pstr_t	file = (pstr_t){.len = strlen(path), .str = path};
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
