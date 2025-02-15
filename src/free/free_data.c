#include <stdlib.h>
#include "indulc.h"
#include "token.h"
#include "macro.h"
#include "label.h"
#include "file.h"

void	free_isa(t_isa* isa)
{
	for (size_t i = 0; i < isa->instructions.len; i++)
		free(((t_instruction *)isa->instructions.arr)[i].format.bitfields.arr);
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

void	close_files(t_data* data)
{
	for (size_t i = 0; i < 3; i++)
		if (data->files[i].stream != NULL)
			fclose(data->files[i].stream);
}

void	free_label(void *label)
{
	free(label);
}

void	free_macro(void *macro)
{
	free(((t_macro *)macro)->value);
	free(macro);
}

void	free_token(void* token)
{
	free(((t_token *)token)->str);
	free(token);
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
