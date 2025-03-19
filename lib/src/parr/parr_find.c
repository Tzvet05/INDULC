#include <stdint.h>
#include "parr.h"

void*	parr_find(t_parr* parr, void* to_find, bool (*cmp)(void*, void*))
{
	uint8_t*	ptr = parr->arr;
	for (size_t i = 0; i < parr->len; i++)
	{
		if (cmp((void *)ptr, to_find) == 1)
			return ((void *)ptr);
		ptr += parr->obj_size;
	}
	return (NULL);
}
