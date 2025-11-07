#include <stdlib.h>

void	free_string(void *string)
{
	free(*(char **)string);
}
