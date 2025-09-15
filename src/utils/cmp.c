#include <stdbool.h>
#include <string.h>
#include "parr.h"
#include "tokenization.h"
#include "preprocessing.h"
#include "symbol_table.h"

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

bool	cmp_mnemonics(void* mnemonics, void* str)
{
	for (size_t i_mnemonic = 0; i_mnemonic < ((t_parr *)mnemonics)->len; i_mnemonic++)
		if (strcmp(((char **)((t_parr *)mnemonics)->arr)[i_mnemonic], str) == 0)
			return (0);
	return (1);
}
