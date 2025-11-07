#include "file.h"
#include "data.h"
#include "signals.h"
#include "json.h"
#include "error.h"

bool	load_blueprint(t_data *data)
{
	if (file_open(&((t_file *)data->files.arr)[INFILE_SIGNALS], FOPEN_READ_MODE) == 1)
	{
		fprintf(stderr, "%s: %s: %s: %s: \"%s\"\n",
			EXECUTABLE_NAME, LIB_LIBC, FUNC_FOPEN, ERROR_OPEN_FILE,
			((t_file *)data->files.arr)[INFILE_SIGNALS].name);
		return (1);
	}
	const cJSON	*json = parse_json_file(&((t_file *)data->files.arr)[INFILE_SIGNALS]);
	file_close(&((t_file *)data->files.arr)[INFILE_SIGNALS]);
	if (json == NULL)
		return (1);
	if (check_blueprint_syntax(json) == 1)
	{
		cJSON_Delete((cJSON *)json);
		return (1);
	}
	if (init_blueprint(&data->blueprint, json) == 1)
	{
		fprintf(stderr, "%s: %s: %s: %s\n",
			EXECUTABLE_NAME, LIB_LIBC, FUNC_MALLOC, ERROR_FAILED_ALLOC);
		free_blueprint(&data->blueprint);
		cJSON_Delete((cJSON *)json);
		return (1);
	}
	cJSON_Delete((cJSON *)json);
	return (0);
}
