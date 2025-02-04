#include <math.h>
#include <string.h>
#include <ctype.h>
#include "indulc.h"

static char*	get_charset(char* str)
{
	if (strncmp(str, HEXA_PREFIX_LOWER, 2) == 0 || strncmp(str, HEXA_PREFIX_UPPER, 2) == 0)
		return (HEXA_CHARSET);
	else if (strncmp(str, BIN_PREFIX, 2) == 0)
		return (BIN_CHARSET);
	else
		return (DEC_CHARSET);
}

bool	is_number(char* str)
{
	size_t	i = 0;
	while (str[i] != '\0'
		&& (str[i] == '+' || str[i] == '-'))
		i++;
	char*	charset = get_charset(&str[i]);
	if (strlen(charset) == 2 || strlen(charset) == 16)
		i += 2;
	while (str[i] != '\0' && strchr(charset, tolower(str[i])) != NULL)
		i++;
	return (str[i] == '\0');
}

bool	will_overflow(char* str, size_t n_bits)
{
	bool	neg = 0;
	size_t	i = 0;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg = !neg;
		i++;
	}
	char*	charset = get_charset(&str[i]);
	if (strlen(charset) == 2 || strlen(charset) == 16)
		i += 2;
	ssize_t	n = (ssize_t)strtoll(&str[i], NULL, strlen(charset));
	if (neg == 1)
		n = -n;
	return (n >= (ssize_t)pow(2.0, (double)(n_bits - 1))
		|| n < -(ssize_t)pow(2.0, (double)(n_bits - 1)));
}

ssize_t	get_number(char* str)
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
	if (radix == 2 || radix == 16)
		i += 2;
	char*	c = strchr(charset, str[i]);
	ssize_t	n = 0;
	while (str[i] != '\0' && c != NULL)
	{
		n = radix * n - (ssize_t)(c - charset);
		i++;
		c = strchr(charset, str[i]);
	}
	return (-n);
}
