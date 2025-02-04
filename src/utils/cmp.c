#include <string.h>
#include <stdbool.h>
#include "token.h"
#include "macro.h"
#include "label.h"

bool	cmp_label(void* label, void* str)
{
	return (strcmp(((t_label *)label)->name, (char *)str) == 0);
}

bool	cmp_macro(void* macro, void* str)
{
	return (strcmp(((t_macro *)macro)->identifier, (char *)str) == 0);
}

bool	cmp_token(void* token, void* str)
{
	return (strcmp(((t_token *)token)->str, (char *)str) == 0);
}
