#include "lst.h"
#include "data.h"
#include "files.h"
#include "arguments.h"
#include "isa.h"
#include "tokenization.h"
#include "preprocessing.h"
#include "symbol_table.h"
#include "syntax.h"
#include "machine_code.h"
#include "error.h"

static bool	assemble(t_data *data)
{
	if (open_file(&((t_file *)data->files.arr)[INFILE_PROGRAM], FOPEN_READ_MODE) == 1)
	{
		fprintf(stderr, "%s: %s: %s: %s: \"%s\"\n",
			EXECUTABLE_NAME, LIB_LIBC, FUNC_FOPEN, ERROR_OPEN_FILE,
			((t_file *)data->files.arr)[INFILE_PROGRAM].name);
		return (1);
	}
	if (tokenize(data) == 1 || preprocess(data) == 1
		|| build_symbol_table(data) == 1 || analyse_syntax(data) == 1)
		return (1);
	if (data->options[OPTION_SYNTAX_ONLY] == YES)
		return (0);
	if (open_file(&((t_file *)data->files.arr)[OUTFILE_PROGRAM], FOPEN_WRITE_MODE) == 1)
	{
		fprintf(stderr, "%s: %s: %s: %s: \"%s\"\n",
			EXECUTABLE_NAME, LIB_LIBC, FUNC_FOPEN, ERROR_OPEN_FILE,
			((t_file *)data->files.arr)[OUTFILE_PROGRAM].name);
		return (1);
	}
	return (generate_machine_code(data));
}

static bool	load_run_free(t_data* data)
{
	if (open_file(&((t_file *)data->files.arr)[INFILE_ISA], FOPEN_READ_MODE) == 1)
	{
		fprintf(stderr, "%s: %s: %s: %s: \"%s\"\n",
			EXECUTABLE_NAME, LIB_LIBC, FUNC_FOPEN, ERROR_OPEN_FILE,
			((t_file *)data->files.arr)[INFILE_ISA].name);
		return (1);
	}
	if (load_isa(data) == 1)
	{
		free_isa(&data->isa);
		close_files(data);
		return (1);
	}
	if (data->options[OPTION_ISA_ONLY] == YES)
	{
		close_files(data);
		return (0);
	}
	bool	error = assemble(data);
	free_isa(&data->isa);
	free_tokens(data->tokens);
	lst_clear(&data->macro_table, free_macro);
	lst_clear(&data->symbol_table, free_label);
	close_files(data);
	return (error);
}

int	main(int argc, char** argv)
{
	(void)argc;
	t_data	data = (t_data){.options = DEFAULT_OPTIONS, .files = DEFAULT_FILES};
	if (get_arguments(&data, &argv[1]) == 1 || check_arguments(&data) == 1)
		return (1);
	bool	error = 0;
	if (exec_options(data.options, &error) == 1)
		return (error);
	if (check_files(&data) == 1)
		return (1);
	return (load_run_free(&data));
}
