#include <stdint.h>
#include "parr.h"

void	*parr_find(parr_t *parr, void *to_find, bool (*cmp)(void*, void*))
{
	uint8_t	*ptr = parr->arr;
	for (size_t i = 0; i < parr->len; i++)
	{
		if (cmp(ptr, to_find) == 0)
			return (ptr);
		ptr += parr->obj_size;
	}
	return (NULL);
}
