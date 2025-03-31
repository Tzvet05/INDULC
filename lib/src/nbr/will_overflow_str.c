#include <ctype.h>
#include <string.h>
#include "nbr.h"

bool	will_overflow_str(char* str, size_t n_bits)
{
	bool	sign = 0;
	size_t	i = 0;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = !sign;
		i++;
	}
	char*	charset = get_charset(&str[i]);
	size_t	radix = strlen(charset);
	if (radix != 10)
		i += 2;
	ssize_t	number = 0;
	char*	ptr_charset = strchr(charset, tolower(str[i]));
	while (str[i] != '\0' && ptr_charset != NULL && number <= 0)
	{
		number = radix * number - (ssize_t)(ptr_charset - charset);
		i++;
		ptr_charset = strchr(charset, tolower(str[i]));
	}
	if (number > 0 || (sign == 0 && number - 1 > 0))
		return (1);
	if (sign == 0)
		number = -number;
	return (will_overflow_int(number, n_bits));
}
