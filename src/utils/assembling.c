#include <string.h>
#include "isa.h"

void*	get_assembling_target(t_isa* isa, char* str, t_mnemonic_type type)
{
	for (size_t i = 0; i < isa->mnemonics.len; i++)
		if (((t_mnemonic *)isa->mnemonics.arr)[i].type == type)
			for (size_t i_mnemonic = 0;
				i_mnemonic < ((t_mnemonic *)isa->mnemonics.arr)[i].mnemonics.len;
				i_mnemonic++)
				if (strcmp(((char **)((t_mnemonic *)isa->mnemonics.arr)[i]
					.mnemonics.arr)[i_mnemonic], str) == 0)
					return (((t_mnemonic *)isa->mnemonics.arr)[i]
						.compilation_target);
	return (NULL);
}
