#include <stdlib.h>
#include <string.h>
#include "libblueprint.h"
#include "data.h"
#include "error.h"

bool	build_string_blueprint(data_t *data)
{
	char	*json = cJSON_PrintUnformatted(data->output.json);
	if (json == NULL)
	{
		fprintf(stderr, "%s: %s: %s: %s: %s\n",
			EXECUTABLE_NAME, ERROR_FUNCTION, LIB_CJSON, FUNC_CJSON_PRINT,
			ERROR_CJSON_PRINT_UNFORMATTED);
		return (1);
	}
	char	*string = blueprint_json_to_string(json);
	free(json);
	if (string == NULL)
	{
		fprintf(stderr, "%s: %s: %s: %s\n",
			EXECUTABLE_NAME, ERROR_LIBRARY, LIB_BLUEPRINT, ERROR_LIBRARY_LOG);
		return (1);
	}
	data->output.string = (parr_t){.len = strlen(string), .obj_size = sizeof(*string),
		.arr = string};
	return (0);
}
