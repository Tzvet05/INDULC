#include <stdbool.h>
#include <string.h>
#include "parr.h"
#include "pstr.h"
#include "tokenization.h"
#include "preprocessing.h"
#include "symbol_table.h"
#include "syntax.h"

bool	cmp_label(void *label, void *str)
{
	return (strcmp(((label_t *)label)->name->str, str) != 0);
}

bool	cmp_macro(void *macro, void *str)
{
	return (strcmp(((macro_t *)macro)->identifier->str, str) != 0);
}

bool	cmp_token(void *token, void *str)
{
	return (strcmp(((token_t *)token)->str, str) != 0);
}

bool	cmp_keyword(void *keyword, void *word)
{
	return (((pstr_t *)word)->len == 0 || strncmp(((keyword_t *)keyword)->str,
		((pstr_t *)word)->str, ((pstr_t *)word)->len) != 0);
}

bool	cmp_mnemonics(void *mnemonics, void *str)
{
	for (size_t i_mnemonic = 0; i_mnemonic < ((parr_t *)mnemonics)->len; i_mnemonic++)
		if (strcmp(((char **)((parr_t *)mnemonics)->arr)[i_mnemonic], str) == 0)
			return (0);
	return (1);
}
