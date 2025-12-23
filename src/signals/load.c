#include "file.h"
#include "pstr.h"
#include "data.h"
#include "signals.h"
#include "json.h"
#include "error.h"

bool	load_blueprint(data_t *data)
{
	if (file_open(&((file_t *)data->files.arr)[INPUT_SIGNALS], FOPEN_MODE_READ) == 1)
	{
		fprintf(stderr, "%s: %s: %s: %s: %s: \"%s\"\n",
			EXECUTABLE_NAME, ERROR_FUNCTION, LIB_LIBC, FUNC_FOPEN, ERROR_OPEN_FILE,
			((file_t *)data->files.arr)[INPUT_SIGNALS].name);
		return (1);
	}
	const cJSON	*json = parse_json_file(&((file_t *)data->files.arr)[INPUT_SIGNALS]);
	file_close(&((file_t *)data->files.arr)[INPUT_SIGNALS]);
	if (json == NULL)
		return (1);
	if (check_blueprint_syntax(json) == 1)
	{
		cJSON_Delete((cJSON *)json);
		return (1);
	}
	pstr_t	input_name = file_get_name(((file_t *)data->files.arr)[INPUT_CODE].name);
	if (init_blueprint(&data->blueprint, &input_name, json) == 1)
	{
		fprintf(stderr, "%s: %s: %s: %s: %s\n",
			EXECUTABLE_NAME, ERROR_FUNCTION, LIB_LIBC, FUNC_MALLOC, ERROR_ALLOC);
		free_blueprint(&data->blueprint);
		cJSON_Delete((cJSON *)json);
		return (1);
	}
	cJSON_Delete((cJSON *)json);
	return (0);
}
