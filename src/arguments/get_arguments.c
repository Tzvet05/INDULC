#include <string.h>
#include "data.h"
#include "arguments.h"
#include "error.h"

static ssize_t	get_option_arguments(t_option* option, char** args, bool parse_options)
{
	size_t	i = 0;
	while (i < option->arguments.len && args[i] != NULL)
	{
		if (parse_options == 1 && is_option(args[i]) == 1)
		{
			fprintf(stderr, "%s: %s: %s: %s: %s: \"%s\"\n",
				EXECUTABLE_NAME, ERROR_ARGUMENT, ERROR_ARGUMENT_OPTION,
				ERROR_ARGUMENT_OPTION_ARGUMENTS,
				ERROR_ARGUMENT_OPTION_ARGUMENTS_OPTION, args[i]);
			return (-1);
		}
		*((char ***)option->arguments.arr)[i] = args[i];
		i++;
	}
	if (i < option->arguments.len)
	{
		fprintf(stderr, "%s: %s: %s: %s: %s\n",
			EXECUTABLE_NAME, ERROR_ARGUMENT, ERROR_ARGUMENT_OPTION,
			ERROR_ARGUMENT_OPTION_ARGUMENTS, ERROR_ARGUMENT_OPTION_ARGUMENTS_TOO_FEW);
		return (-1);
	}
	return ((ssize_t)i);
}

static bool	get_parameter(t_option* option, char* arg, t_option_parameter* parameter)
{
	char*	beginning_parameter = strchr(arg, '=');
	if (beginning_parameter == NULL || *(beginning_parameter + 1) == '\0')
	{
		fprintf(stderr, "%s: %s: %s: %s: %s: \"%s\"\n",
			EXECUTABLE_NAME, ERROR_ARGUMENT, ERROR_ARGUMENT_OPTION,
			ERROR_ARGUMENT_OPTION_PARAM, ERROR_ARGUMENT_OPTION_PARAM_TOO_FEW, arg);
		return (1);
	}
	beginning_parameter++;
	size_t	i_parameter = 0;
	while (i_parameter < option->parameters.len)
	{
		if (strcmp(((t_parameter *)option->parameters.arr)[i_parameter].name,
			beginning_parameter) == 0)
		{
			*parameter = ((t_parameter *)option->parameters.arr)[i_parameter].parameter;
			return (0);
		}
		i_parameter++;
	}
	fprintf(stderr, "%s: %s: %s: %s: %s: \"%s\"\n",
		EXECUTABLE_NAME, ERROR_ARGUMENT, ERROR_ARGUMENT_OPTION, ERROR_ARGUMENT_OPTION_PARAM,
		ERROR_ARGUMENT_OPTION_PARAM_INVALID, arg);
	return (1);
}

static ssize_t	get_i_option(const t_parr* options, char* arg)
{
	size_t	i_option = 0;
	while (i_option < options->len)
	{
		size_t	i_name = 0;
		char*	name = ((t_option *)options->arr)[i_option].names[i_name];
		while (name != NULL)
		{
			size_t	len_name = strlen(name);
			if (strncmp(name, arg, len_name) == 0
				&& (arg[len_name] == '=' || arg[len_name] == '\0'))
				return ((ssize_t)i_option);
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
	size_t	i_arg = 0;
	while (args[i_arg] != NULL)
	{
		if (parse_options == 1 && is_option(args[i_arg]) == 1)
		{
			if (strcmp(args[i_arg], OPTION_PARSING_END) == 0)
				parse_options = 0;
			else
			{
				ssize_t	i_option = get_i_option(&options, args[i_arg]);
				if (i_option == -1)
				{
					fprintf(stderr, "%s: %s: %s: %s: \"%s\"\n",
						EXECUTABLE_NAME, ERROR_ARGUMENT,
						ERROR_ARGUMENT_OPTION, ERROR_ARGUMENT_OPTION_NAME,
						args[i_arg]);
					return (1);
				}
				t_option*	option = &((t_option *)options.arr)[i_option];
				t_option_parameter	parameter = YES;
				if (option->parameters.len > 0)
				{
					if (get_parameter(option, args[i_arg], &parameter) == 1)
						return (1);
				}
				else if (has_parameter(args[i_arg]) == 1)
				{
					fprintf(stderr, "%s: %s: %s: %s: %s: \"%s\"\n",
						EXECUTABLE_NAME, ERROR_ARGUMENT,
						ERROR_ARGUMENT_OPTION, ERROR_ARGUMENT_OPTION_PARAM,
						ERROR_ARGUMENT_OPTION_PARAM_TOO_MANY, args[i_arg]);
					return (1);
				}
				data->options[i_option] = parameter;
				if (option->arguments.len > 0)
				{
					ssize_t	args_to_skip = get_option_arguments(option,
						&args[i_arg + 1], parse_options);
					if (args_to_skip == -1)
						return (1);
					i_arg += (size_t)args_to_skip;
				}
			}
		}
		else
		{
			if (data->files[INFILE_PROGRAM].name == NULL)
				data->files[INFILE_PROGRAM].name = args[i_arg];
			else
			{
				fprintf(stderr, "%s: %s: %s: \"%s\"\n",
					EXECUTABLE_NAME, ERROR_ARGUMENT,
					ERROR_ARGUMENT_TOO_MANY, args[i_arg]);
				return (1);
			}
		}
		i_arg++;
	}
	return (0);
}
