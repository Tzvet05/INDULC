#include <string.h>
#include "data.h"
#include "arguments.h"
#include "option.h"
#include "error.h"

static bool	is_option(char* str)
{
	return (str[0] == '-');
}

static ssize_t	get_value(t_option* option, char* arg)
{
	char*	beginning_value = strchr(arg, '=');
	if (beginning_value == NULL)
		return (-1);
	beginning_value++;
	for (size_t i_value = 0; i_value < 2; i_value++)
		if (strcmp(option->values[i_value], beginning_value) == 0)
			return (i_value);
	return (-1);
}

static ssize_t	get_option(const t_parr* options, char* arg)
{
	char*	end_name = strchr(arg, '=');
	if (end_name == NULL)
		end_name = &arg[strlen(arg)];
	size_t	i_option = 0;
	while (i_option < options->len)
	{
		size_t	i_name = 0;
		char*	name = ((t_option *)options->arr)[i_option].names[i_name];
		while (name != NULL)
		{
			if (strncmp(name, arg, strlen(name)) == 0
				&& strlen(name) == (size_t)(end_name - arg))
				return (i_option);
			i_name++;
			name = ((t_option *)options->arr)[i_option].names[i_name];
		}
		i_option++;
	}
	return (-1);
}

bool	get_arguments(t_data* data, char** args)
{
	const t_parr	options = OPTIONS;
	bool	parse_options = 1;
	size_t	i_arg = 0, i_file = 0;
	while (args[i_arg] != NULL)
	{
		if (parse_options == 1 && is_option(args[i_arg]) == 1)
		{
			if (strcmp(args[i_arg], "--") == 0)
				parse_options = 0;
			else
			{
				ssize_t	i_option = get_option(&options, args[i_arg]);
				if (i_option == -1)
				{
					fprintf(stderr, "%s: %s: %s: \"%s\"\n",
						EXECUTABLE_NAME, ERROR_ARGUMENT,
						ERROR_ARGUMENT_OPTION_NAME, args[i_arg]);
					return (1);
				}
				else
				{
					ssize_t	i_value = 1;
					if (((t_option *)options.arr)[i_option].values != NULL)
					{
						i_value = get_value(&((t_option *)options
							.arr)[i_option], args[i_arg]);
						if (i_value == -1)
						{
							fprintf(stderr, "%s: %s: %s: \"%s\"\n",
								EXECUTABLE_NAME, ERROR_ARGUMENT,
								ERROR_ARGUMENT_OPTION_VALUE,
								args[i_arg]);
							return (1);
						}
					}
					data->options |= (uint8_t)i_value << (uint8_t)i_option;
				}
			}
		}
		else
		{
			if (i_file >= 3)
			{
				fprintf(stderr, "%s: %s: %s: \"%s\"\n",
					EXECUTABLE_NAME, ERROR_ARGUMENT,
					ERROR_ARGUMENT_TOO_MANY_FILES, args[i_arg]);
				return (1);
			}
			data->files[i_file].name = args[i_arg];
			i_file++;
		}
		i_arg++;
	}
	if (i_file == 0
		&& !(data->options & OPTION_VERSION) && !(data->options & OPTION_HELP))
	{
		fprintf(stderr, "%s: %s: %s\n",
			EXECUTABLE_NAME, ERROR_ARGUMENT, ERROR_ARGUMENT_TOO_FEW_FILES);
		return (1);
	}
	const char* const	files[] = DEFAULT_FILES;
	while (i_file < 3)
	{
		data->files[i_file].name = (char *)files[i_file - 1];
		i_file++;
	}
	return (0);
}
