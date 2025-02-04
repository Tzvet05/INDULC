#include "indulc.h"

static bool	compiling(t_data *data)
{
	if (tokenization(data) == 1)
	{
		free_isa(&data->isa);
		close_files(data);
		free_tokens(data->tokens);
		return (1);
	}
	else if (preprocessing(data) == 1)
	{
		free_isa(&data->isa);
		close_files(data);
		free_tokens(data->tokens);
		lst_clear(&data->macro_table, free_macro);
		return (1);
	}
	else if (symbol_table_building(data) == 1)
	{
		free_isa(&data->isa);
		close_files(data);
		free_tokens(data->tokens);
		lst_clear(&data->macro_table, free_macro);
		lst_clear(&data->symbol_table, free_label);
		return (1);
	}
	else if (syntax_analysis(data) == 1)
	{
		free_isa(&data->isa);
		close_files(data);
		free_tokens(data->tokens);
		lst_clear(&data->macro_table, free_macro);
		lst_clear(&data->symbol_table, free_label);
		return (1);
	}
	else if (machine_code_generation(data) == 1)
	{
		free_isa(&data->isa);
		close_files(data);
		free_tokens(data->tokens);
		lst_clear(&data->macro_table, free_macro);
		lst_clear(&data->symbol_table, free_label);
		return (1);
	}
	else
		return (0);
}

int	main(int argc, char** argv)
{
	if (argument_checking(argc, argv) == 1)
		return (1);
	t_data	data = {.files.len = argc - 1};
	if (isa_loading(&data) == 1)
	{
		free_isa(&data.isa);
		return (1);
	}
	if (file_opening(&data, &argv[1]) == 1)
	{
		free_isa(&data.isa);
		close_files(&data);
		return (1);
	}
	if (compiling(&data) == 1)
		return (1);
	free_isa(&data.isa);
	free_tokens(data.tokens);
	lst_clear(&data.macro_table, free_macro);
	lst_clear(&data.symbol_table, free_label);
	close_files(&data);
	return (0);
}
