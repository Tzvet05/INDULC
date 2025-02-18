#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "nbr.h"

bool	will_overflow(char* str, size_t n_bits)
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
	return (n >= (ssize_t)pow(2.0, (double)(n_bits - 1))
		|| n < -(ssize_t)pow(2.0, (double)(n_bits - 1)));
}
