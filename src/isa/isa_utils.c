#include <string.h>
#include "isa.h"

ssize_t	get_bitfield_type(char* str)
{
	static const char* const	type_strings[] = BITFIELD_TYPES;
	t_bitfield_type	type = REGISTER;
	while (type < N_BITFIELD_TYPES && strcmp(str, type_strings[type]) != 0)
		type++;
	if (type == N_BITFIELD_TYPES)
		return (-1);
	return ((ssize_t)type);
}
