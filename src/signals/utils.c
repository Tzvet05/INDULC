#include <sys/types.h>
#include <string.h>
#include "parr.h"

char	*get_type(t_parr *types, char *type)
{
	for (size_t i = 0; i < types->len; i++)
		if (strcmp(((char **)types->arr)[i], type) == 0)
			return (((char **)types->arr)[i]);
	return (NULL);
}

ssize_t	get_i_type(t_parr *types, char *type)
{
	for (size_t i = 0; i < types->len; i++)
		if (strcmp(((char **)types->arr)[i], type) == 0)
			return ((ssize_t)i);
	return (-1);
}

