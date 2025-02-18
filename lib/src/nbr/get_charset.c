#include <string.h>
#include "nbr.h"

char*	get_charset(char* str)
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
