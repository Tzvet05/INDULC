#include <string.h>
#include <stdlib.h>
#include "nbr.h"

ssize_t	get_number(char* str)
{
	bool	sign = 0;
	size_t	i = 0;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = !sign;
		i++;
	}
	char*	charset = get_charset(&str[i]);
	size_t	radix = strlen(charset);
	if (radix == 2 || radix == 16)
		i += 2;
	ssize_t	n = (ssize_t)strtoll(&str[i], NULL, radix);
	if (sign == 1)
		n = -n;
	return (n);
}
