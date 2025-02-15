#include <stdint.h>
#include <string.h>
#include "lst.h"
#include "parr.h"

bool	lst_to_parr(t_lst* lst, t_parr* parr)
{
	parr->len = lst_size(lst);
	if (parr->len == 0)
		parr->arr = NULL;
	else
	{
		parr->arr = malloc(parr->len * sizeof(*lst->content));
		if (parr->arr == NULL)
		{
			parr->len = 0;
			return (1);
		}
		uint8_t*	element = (uint8_t *)parr->arr;
		for (size_t i = 0; i < parr->len; i++)
		{
			memcpy((void *)element, lst->content, sizeof(*lst->content));
			element += sizeof(*lst->content);
			lst = lst->next;
		}
	}
	return (0);
}
