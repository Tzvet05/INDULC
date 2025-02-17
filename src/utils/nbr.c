#include <math.h>
#include <string.h>
#include <ctype.h>
#include "indulc.h"

static char*	get_charset(char* str)
{
	if (strncmp(str, HEX_PREFIX, strlen(HEX_PREFIX)) == 0)
		return (HEX_CHARSET);
	else if (strncmp(str, OCT_PREFIX, strlen(OCT_PREFIX)) == 0)
		return (OCT_CHARSET);
	else if (strncmp(str, BIN_PREFIX, strlen(BIN_PREFIX)) == 0)
		return (BIN_CHARSET);
	else
		return (DEC_CHARSET);
}

bool	is_number(char* str)
{
	size_t	i = 0;
	while (str[i] != '\0' && (str[i] == '+' || str[i] == '-'))
		i++;
	char*	charset = get_charset(&str[i]);
	size_t	radix = strlen(charset);
	if (radix == 2 || radix == 16)
		i += 2;
	while (str[i] != '\0' && strchr(charset, tolower(str[i])) != NULL)
		i++;
	return (str[i] == '\0');
}

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
