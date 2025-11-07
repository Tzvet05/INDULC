#include <stdint.h>
#include <stdlib.h>
#include "parr.h"

void	parr_clear(t_parr *parr, void (*del)(void*))
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
	*parr = (t_parr){0};
}
