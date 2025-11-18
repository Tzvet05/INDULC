#include "file.h"
#include "data.h"
#include "json.h"
#include "error.h"

static void	set_instruction_data(t_isa *isa)
{
	for (size_t i_instruction = 0; i_instruction < isa->instructions.len; i_instruction++)
	{
		size_t	n_opwords = 0;
		for (size_t i_bitfield = 0;
			i_bitfield < ((t_instruction *)isa->instructions.arr)[i_instruction]
			.bitfields.len; i_bitfield++)
			if (((t_bitfield *)((t_instruction *)isa->instructions.arr)[i_instruction]
				.bitfields.arr)[i_bitfield].type != CONSTANT)
				n_opwords++;
		((t_instruction *)isa->instructions.arr)[i_instruction].n_opwords = n_opwords;
	}
}

bool	load_isa(t_data *data)
{
	if (file_open(&((t_file *)data->files.arr)[INPUT_ISA], FOPEN_READ_MODE) == 1)
	{
		fprintf(stderr, "%s: %s: %s: %s: \"%s\"\n",
			EXECUTABLE_NAME, LIB_LIBC, FUNC_FOPEN, ERROR_OPEN_FILE,
			((t_file *)data->files.arr)[INPUT_ISA].name);
		return (1);
	}
	const cJSON	*json = parse_json_file(&((t_file *)data->files.arr)[INPUT_ISA]);
	file_close(&((t_file *)data->files.arr)[INPUT_ISA]);
	if (json == NULL)
		return (1);
	if (check_isa_syntax(json) == 1)
	{
		cJSON_Delete((cJSON *)json);
		return (1);
	}
	if (data->options[OPTION_ISA_ONLY] == PARAM_YES)
	{
		cJSON_Delete((cJSON *)json);
		return (0);
	}
	if (init_isa(&data->isa, json) == 1)
	{
		fprintf(stderr, "%s: %s: %s: %s\n",
			EXECUTABLE_NAME, LIB_LIBC, FUNC_MALLOC, ERROR_FAILED_ALLOC);
		free_isa(&data->isa);
		cJSON_Delete((cJSON *)json);
		return (1);
	}
	cJSON_Delete((cJSON *)json);
	set_instruction_data(&data->isa);
	return (0);
}
