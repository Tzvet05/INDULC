#include <string.h>
#include "isa.h"

t_instruction*	get_instruction(t_isa* isa, char* instruction)
{
	for (size_t i_instruction = 0; i_instruction < isa->instructions.len; i_instruction++)
		for (size_t i_mnemonic = 0; i_mnemonic < ((t_instruction *)isa->instructions.arr)
			[i_instruction].mnemonics.len; i_mnemonic++)
			if (strcmp(((char **)((t_instruction *)isa->instructions.arr)
				[i_instruction].mnemonics.arr)[i_mnemonic], instruction) == 0)
				return (&((t_instruction *)isa->instructions.arr)[i_instruction]);
	return (NULL);
}

t_flag*	get_flag(t_isa* isa, char* flag)
{
	for (size_t i_flag = 0; i_flag < isa->flags.len; i_flag++)
		for (size_t i_mnemonic = 0;
			i_mnemonic < ((t_flag *)isa->flags.arr)[i_flag].mnemonics.len; i_mnemonic++)
			if (strcmp(((char **)((t_flag *)isa->flags.arr)
				[i_flag].mnemonics.arr)[i_mnemonic], flag) == 0)
				return (&((t_flag *)isa->flags.arr)[i_flag]);
	return (NULL);
}

t_register*	get_register(t_isa* isa, char* _register)
{
	for (size_t i_register = 0; i_register < isa->registers.len; i_register++)
		for (size_t i_mnemonic = 0;
			i_mnemonic < ((t_register *)isa->registers.arr)[i_register].mnemonics.len;
			i_mnemonic++)
			if (strcmp(((char **)((t_register *)isa->registers.arr)
				[i_register].mnemonics.arr)[i_mnemonic], _register) == 0)
				return (&((t_register *)isa->registers.arr)[i_register]);
	return (NULL);
}
