#include "indulc.h"

static bool	compiling(t_data *data)
{
	if (input_file_opening(data) == 1)
		return (1);
	else if (tokenization(data) == 1)
		return (1);
	else if (preprocessing(data) == 1)
		return (1);
	else if (symbol_table_building(data) == 1)
		return (1);
	else if (syntax_analysis(data) == 1)
		return (1);
	else if (output_file_opening(data) == 1)
		return (1);
	else 
		return (machine_code_generation(data));
}

int	main(int argc, char** argv)
{
	if (argument_checking(argc, argv) == 1)
		return (1);
	t_data	data = {0};
	if (isa_loading(&data) == 1)
	{
		free_isa(&data.isa);
		return (1);
	}
	init_filename(&data, &argv[1]);
	bool	error = compiling(&data);
	free_isa(&data.isa);
	close_files(&data);
	free_tokens(data.tokens);
	lst_clear(&data.macro_table, free_macro);
	lst_clear(&data.symbol_table, free_label);
	return (error);
}
