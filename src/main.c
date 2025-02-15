#include "indulc.h"
#include "file.h"

static bool	compilation(t_data *data)
{
	if (open_file(&data->files[INFILE_PROGRAM], READ_MODE) == 1)
		return (1);
	else if (tokenization(data) == 1)
		return (1);
	else if (preprocessing(data) == 1)
		return (1);
	else if (symbol_table_building(data) == 1)
		return (1);
	else if (syntax_analysis(data) == 1)
		return (1);
	else if (open_file(&data->files[OUTFILE_PROGRAM], WRITE_MODE) == 1)
		return (1);
	else 
		return (machine_code_generation(data));
}

int	main(int argc, char** argv)
{
	if (argument_checking(argc, argv) == 1)
		return (1);
	t_data	data = {0};
	init_filenames(&data, &argv[1]);
	if (open_file(&data.files[INFILE_ISA], READ_MODE) == 1 || isa_loading(&data) == 1)
	{
		free_isa(&data.isa);
		close_files(&data);
		return (1);
	}
	bool	error = compilation(&data);
	free_isa(&data.isa);
	close_files(&data);
	free_tokens(data.tokens);
	lst_clear(&data.macro_table, free_macro);
	lst_clear(&data.symbol_table, free_label);
	return (error);
}
