#include <math.h>
#include <stddef.h>
#include <string.h>
#include <stdint.h>
#include "isa.h"

uint64_t	build_mask(size_t len)
{
	return ((uint64_t)pow(2.0, (double)len) - 1);
}

void*	get_compilation_target(t_isa* isa, char* str, t_mnemonic_type type)
{
	size_t	i = 0;
	while (i < isa->mnemonics.len)
	{
		if (((t_mnemonic *)isa->mnemonics.arr)[i].type == type)
		{
			size_t	i_mnemonic = 0;
			while (i_mnemonic < ((t_mnemonic *)isa->mnemonics.arr)[i].mnemonics.len)
			{
				if (strcmp(((char **)((t_mnemonic *)isa->mnemonics.arr)[i]
					.mnemonics.arr)[i_mnemonic], str) == 0)
					return (((t_mnemonic *)isa->mnemonics.arr)[i]
						.compilation_target);
				i_mnemonic++;
			}
		}
		i++;
	}
	return (NULL);
}
