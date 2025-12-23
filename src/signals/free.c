#include <stdlib.h>
#include <string.h>
#include "signals.h"
#include "free.h"

static void	free_signal(void *signal)
{
	free(((signal_t *)signal)->name);
}

void	free_blueprint(blueprint_t *blueprint)
{
	free(blueprint->text[LABEL]);
	free(blueprint->text[DESCRIPTION]);
	bzero(blueprint->text, N_TEXTS * sizeof(char *));
	parr_clear(&blueprint->types, free_string);
	parr_clear(&blueprint->qualities, free_string);
	parr_clear(&blueprint->signals, free_signal);
}
