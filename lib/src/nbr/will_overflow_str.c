#include <string.h>
#include <stdlib.h>
#include "nbr.h"
#include "bit.h"

bool	will_overflow_str(char* str, size_t n_bits)
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
	ssize_t	extremum = (ssize_t)build_mask(n_bits - (n_bits > 0));
	return (n > extremum || n < ~extremum);
}
