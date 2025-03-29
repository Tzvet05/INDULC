#include <stdlib.h>
#include "isa.h"

void	free_isa(t_isa* isa)
{
	for (size_t i_instruction = 0; i_instruction < isa->instructions.len; i_instruction++)
	{
		for (size_t i_mnemonic = 0; i_mnemonic < ((t_instruction *)isa->instructions.arr)
			[i_instruction].mnemonics.len; i_mnemonic++)
			free(((char **)((t_instruction *)isa->instructions.arr)
				[i_instruction].mnemonics.arr)[i_mnemonic]);
		free(((t_instruction *)isa->instructions.arr)[i_instruction].mnemonics.arr);
		free(((t_instruction *)isa->instructions.arr)[i_instruction].bitfields.arr);
	}
	free(isa->instructions.arr);
	for (size_t i_flag = 0; i_flag < isa->flags.len; i_flag++)
	{
		for (size_t i_mnemonic = 0; i_mnemonic < ((t_flag *)isa->flags.arr)
			[i_flag].mnemonics.len; i_mnemonic++)
			free(((char **)((t_flag *)isa->flags.arr)
				[i_flag].mnemonics.arr)[i_mnemonic]);
		free(((t_flag *)isa->flags.arr)[i_flag].mnemonics.arr);
	}
	free(isa->flags.arr);
	for (size_t i_register = 0; i_register < isa->registers.len; i_register++)
	{
		for (size_t i_mnemonic = 0;
			i_mnemonic < ((t_register *)isa->registers.arr)[i_register].mnemonics.len;
			i_mnemonic++)
			free(((char **)((t_register *)isa->registers.arr)
				[i_register].mnemonics.arr)[i_mnemonic]);
		free(((t_register *)isa->registers.arr)[i_register].mnemonics.arr);
	}
	free(isa->registers.arr);
}
