#include "execution.h"
#include "data.h"
#include "files.h"
#include "macro.h"
#include "label.h"
#include "token.h"
#include "error.h"

static bool	assemble(t_data *data)
{
	if (open_file(&data->files[INFILE_PROGRAM], FOPEN_READ_MODE) == 1)
	{
		fprintf(stderr, "%s: %s: %s: \"%s\"\n",
			EXECUTABLE_NAME, FUNC_FOPEN, ERROR_OPEN_FILE,
			data->files[INFILE_PROGRAM].name);
		return (1);
	}
	else if (tokenize(data) == 1)
		return (1);
	else if (preprocess(data) == 1)
		return (1);
	else if (build_symbol_table(data) == 1)
		return (1);
	else if (analyse_syntax(data) == 1)
		return (1);
	else if (open_file(&data->files[OUTFILE_PROGRAM], FOPEN_WRITE_MODE) == 1)
	{
		fprintf(stderr, "%s: %s: %s: \"%s\"\n",
			EXECUTABLE_NAME, FUNC_FOPEN, ERROR_OPEN_FILE,
			data->files[OUTFILE_PROGRAM].name);
		return (1);
	}
	else 
		return (generate_machine_code(data));
}

int	main(int argc, char** argv)
{
	if (check_arguments(argc - 1) == 1)
		return (1);
	t_data	data = {0};
	init_filenames(&data, &argv[1]);
	if (check_files(&data) == 1)
		return (1);
	if (open_file(&data.files[INFILE_ISA], FOPEN_READ_MODE) == 1 || load_isa(&data) == 1)
	{
		free_isa(&data.isa);
		close_files(&data);
		return (1);
	}
	bool	error = assemble(&data);
	free_isa(&data.isa);
	close_files(&data);
	free_tokens(data.tokens);
	lst_clear(&data.macro_table, free_macro);
	lst_clear(&data.symbol_table, free_label);
	return (error);
}
