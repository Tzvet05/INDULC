#include <stdbool.h>
#include <string.h>

bool	is_option(char* str)
{
	return (str[0] == '-');
}

bool	has_parameter(char* str)
{
	return (strchr(str, '=') != NULL);
}
