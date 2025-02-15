#include <stdint.h>
#include "parr.h"

void*	parr_find(t_parr* parr, void* to_find, bool (*cmp)(void*, void*), size_t size)
{
	uint8_t*	ptr = parr->arr;
	size_t	i = 0;
	while (i < parr->len)
	{
		if (cmp((void *)ptr, to_find) == 1)
			return ((void *)ptr);
		ptr += size;
		i++;
	}
	return (NULL);
}
