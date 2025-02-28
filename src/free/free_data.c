#include <stdlib.h>
#include "indulc.h"

void	free_isa(t_isa* isa)
{
	free(isa->registers.arr);
	for (size_t i_instruction = 0; i_instruction < isa->instructions.len; i_instruction++)
		free(((t_instruction *)isa->instructions.arr)[i_instruction].bitfields.arr);
	free(isa->instructions.arr);
	free(isa->flags.arr);
	for (size_t i = 0; i < isa->mnemonics.len; i++)
	{
		for (size_t i_mnemonic = 0;
			i_mnemonic < ((t_mnemonic *)isa->mnemonics.arr)[i].mnemonics.len;
			i_mnemonic++)
			free(((char **)((t_mnemonic *)isa->mnemonics.arr)[i]
				.mnemonics.arr)[i_mnemonic]);
		free(((t_mnemonic *)isa->mnemonics.arr)[i].mnemonics.arr);
	}
	free(isa->mnemonics.arr);
}

void	free_tokens(t_lst* token_col)
{
	t_lst*	token_lin;
	token_lin = token_col;
	while (token_lin != NULL)
	{
		lst_clear((t_lst **)&(token_lin->content), free_token);
		token_lin = token_lin->next;
	}
	lst_clear(&token_col, free);
}
