#include <stdlib.h>
#include "lst.h"
#include "file.h"
#include "data.h"
#include "tokenization.h"
#include "preprocessing.h"
#include "symbol_table.h"
#include "syntax.h"
#include "machine_code.h"
#include "signals.h"
#include "blueprint.h"
#include "output_writing.h"
#include "error.h"

static bool	assemble(t_data *data)
{
	if (tokenize(data) == 1 || preprocess(data) == 1 || build_symbol_table(data) == 1
		|| analyse_syntax(data) == 1)
		return (1);
	if (data->options[OPTION_SYNTAX_ONLY] == PARAM_YES
		|| (data->options[OPTION_MACHINE_CODE_OUTPUT] == PARAM_NO
		&& data->options[OPTION_JSON_OUTPUT] == PARAM_NO
		&& data->options[OPTION_STRING_OUTPUT] == PARAM_NO))
		return (0);
	return (generate_machine_code(data));
}

static bool	convert_output(t_data *data)
{
	if (data->options[OPTION_MACHINE_CODE_OUTPUT] != PARAM_NO
		&& write_machine_code(&data->output.machine_code,
		&((t_file *)data->files.arr)[OUTFILE_MACHINE_CODE], data->options) == 1)
		return (1);
	if (data->isa.instruction_length > 32
		|| (data->options[OPTION_JSON_OUTPUT] == PARAM_NO
		&& data->options[OPTION_STRING_OUTPUT] == PARAM_NO))
		return (0);
	if (load_blueprint(data) == 1)
		return (1);
	if (build_json_blueprint(data) == 1)
	{
		fprintf(stderr, "%s: %s: %s: %s\n",
			EXECUTABLE_NAME, LIB_CJSON, FUNC_CJSON_CREATE_OBJECT,
			ERROR_CJSON_CREATE_OBJECT);
		return (1);
	}
	if (data->options[OPTION_JSON_OUTPUT] != PARAM_NO
		&& write_json(data->output.json, &((t_file *)data->files.arr)[OUTFILE_JSON],
		data->options) == 1)
		return (1);
	if (data->options[OPTION_STRING_OUTPUT] == PARAM_NO)
		return (0);
	if (data->options[OPTION_STRING_OUTPUT] != PARAM_NO
		&& (build_string_blueprint(data) == 1 || write_string(&data->output.string,
		&((t_file *)data->files.arr)[OUTFILE_STRING], data->options) == 1))
			return (1);
	return (0);
}

static bool	run(t_data *data)
{
	if (load_isa(data) == 1)
		return (1);
	if (data->options[OPTION_ISA_ONLY] == PARAM_YES)
		return (0);
	bool	error = assemble(data);
	free_isa(&data->isa);
	free_tokens(&data->tokens);
	lst_clear(&data->macro_table, free_macro);
	lst_clear(&data->symbol_table, free_label);
	if (error == 1 || data->options[OPTION_SYNTAX_ONLY] == PARAM_YES)
		return (error);
	error = convert_output(data);
	free_blueprint(&data->blueprint);
	free(data->output.machine_code.arr);
	cJSON_Delete(data->output.json);
	free(data->output.string.arr);
	return (error);
}

int32_t	main(int32_t argc, char **argv)
{
	(void)argc;
	t_data	data = (t_data){.options = DEFAULT_OPTIONS};
	if (alloc_files(&data) == 1 || get_arguments(&data, &argv[1]) == 1
		|| check_arguments(&data) == 1)
	{
		parr_clear(&data.files, file_free);
		return (1);
	}
	bool	error = 0;
	if (exec_options(data.options, &error) == 1)
	{
		parr_clear(&data.files, file_free);
		return (error);
	}
	if (init_files(&data) == 1 || check_files(&data) == 1 || run(&data) == 1)
		error = 1;
	parr_clear(&data.files, file_free);
	return (error);
}
