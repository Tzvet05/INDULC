#include <stdlib.h>
#include "indulc.h"
#include "token.h"
#include "macro.h"
#include "label.h"

void	free_label(void *label)
{
	free(label);
}

void	free_macro(void *macro)
{
	free(((t_macro *)macro)->value);
	free(macro);
}

void	free_token(void* token)
{
	free(((t_token *)token)->str);
	free(token);
}
