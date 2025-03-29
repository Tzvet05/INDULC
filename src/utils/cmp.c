#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include "token.h"
#include "macro.h"
#include "label.h"
#include "isa.h"

bool	cmp_label(void* label, void* str)
{
	return (strcmp(((t_label *)label)->name->str, (char *)str) != 0);
}

bool	cmp_macro(void* macro, void* str)
{
	return (strcmp(((t_macro *)macro)->identifier->str, (char *)str) != 0);
}

bool	cmp_token(void* token, void* str)
{
	return (strcmp(((t_token *)token)->str, (char *)str) != 0);
}

bool	cmp_flag(void* flag, void *ptr)
{
	return ((ssize_t)((t_flag *)flag)->code != *(ssize_t *)ptr);
}

bool	cmp_register(void* _register, void* ptr)
{
	return ((ssize_t)((t_register *)_register)->index != *(ssize_t *)ptr);
}
