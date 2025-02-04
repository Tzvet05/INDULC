#include <stdlib.h>
#include "indulc.h"
#include "token.h"
#include "macro.h"
#include "label.h"
#include "file.h"

void	free_isa(t_isa* isa)
{
	size_t	i = 0;
	while (i < isa->instructions.len)
	{
		free(((t_instruction *)isa->instructions.arr)[i].bitfields.arr);
		i++;
	}
	free(isa->instructions.arr);
	free(isa->flags.arr);
	i = 0;
	while (i < isa->mnemonics.len)
	{
		size_t i_mnemonic = 0;
		while (((t_mnemonic *)isa->mnemonics.arr)[i].mnemonic[i_mnemonic] != NULL)
		{
			free(((t_mnemonic *)isa->mnemonics.arr)[i].mnemonic[i_mnemonic]);
			i_mnemonic++;
		}
		free(((t_mnemonic *)isa->mnemonics.arr)[i].mnemonic);
		i++;
	}
	free(isa->mnemonics.arr);
}

void	close_files(t_data* data)
{
	size_t	i = 0;
	while (i < data->files.len)
	{
		if (((t_file *)data->files.arr)[i].stream != NULL)
			fclose(((t_file *)data->files.arr)[i].stream);
		i++;
	}
	free(data->files.arr);
}

void	free_label(void *label)
{
	free(((t_label *)label)->name);
	free(label);
}

void	free_macro(void *macro)
{
	free(((t_macro *)macro)->identifier);
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
