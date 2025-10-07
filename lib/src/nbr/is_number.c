#include <ctype.h>
#include <string.h>
#include "nbr.h"

bool	is_number(char* str)
{
	size_t	i = 0;
	while (str[i] == '+' || str[i] == '-')
		i++;
	char*	charset = get_charset(&str[i]);
	if (strlen(charset) != 10)
		i += 2;
	while (str[i] != '\0' && strchr(charset, tolower(str[i])) != NULL)
		i++;
	return (str[i] == '\0');
}
