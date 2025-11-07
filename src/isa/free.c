#include <stdlib.h>
#include "isa.h"
#include "free.h"

static void	free_instruction(void *instruction)
{
	parr_clear(&((t_instruction *)instruction)->mnemonics, free_string);
	parr_clear(&((t_instruction *)instruction)->bitfields, NULL);
}

static void	free_flag(void *flag)
{
	parr_clear(&((t_flag *)flag)->mnemonics, free_string);
}

static void	free_register(void *_register)
{
	parr_clear(&((t_register *)_register)->mnemonics, free_string);
}

void	free_isa(t_isa *isa)
{
	parr_clear(&isa->registers, free_register);
	parr_clear(&isa->flags, free_flag);
	parr_clear(&isa->instructions, free_instruction);
}
