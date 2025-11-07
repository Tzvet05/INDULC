#include <stdlib.h>
#include "signals.h"
#include "free.h"

static void	free_signal(void *signal)
{
	free(((t_signal *)signal)->name);
}

void	free_blueprint(t_blueprint *blueprint)
{
	parr_clear(&blueprint->types, free_string);
	parr_clear(&blueprint->qualities, free_string);
	parr_clear(&blueprint->signals, free_signal);
}
