#include <stdint.h>
#include <stdlib.h>
#include "parr.h"

void	parr_clear(parr_t *parr, void (*del)(void*))
{
	if (del != NULL)
	{
		uint8_t	*ptr = parr->arr;
		for (size_t i = 0; i < parr->len; i++)
		{
			del(ptr);
			ptr += parr->obj_size;
		}
	}
	free(parr->arr);
	*parr = (parr_t){0};
}
