#include <string.h>
#include <ctype.h>
#include "nbr.h"

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
