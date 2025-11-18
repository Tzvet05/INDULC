#include <string.h>
#include <stdlib.h>
#include "file.h"
#include "data.h"
#include "arguments.h"
#include "is.h"
#include "error.h"

static ssize_t	get_option_arguments(t_parr *arguments, char **args, bool parse_options)
{
	size_t	i_argument = 0;
	while (i_argument < arguments->len
		&& ((t_argument *)arguments->arr)[i_argument].src != NULL)
	{
		t_argument	*argument = &((t_argument *)arguments->arr)[i_argument];
		if (argument->type == DUP)
		{
			uint8_t	**dst = argument->dst;
			free(*dst);
			*dst = malloc(argument->size);
			if (*dst == NULL)
			{
				fprintf(stderr, "%s: %s: %s: %s\n",
					EXECUTABLE_NAME, LIB_LIBC, FUNC_MALLOC, ERROR_FAILED_ALLOC);
				return (-1);
			}
			memcpy(*dst, argument->src, argument->size);
		}
		else
			memcpy(argument->dst, argument->src, argument->size);
		i_argument++;
	}
	size_t	i_string = 0;
	while (i_argument < arguments->len && args[i_string] != NULL)
	{
		if (parse_options == 1 && is_option(args[i_string]) == 1)
		{
			fprintf(stderr, "%s: %s: %s: %s: %s: \"%s\"\n",
				EXECUTABLE_NAME, ERROR_ARGUMENT, ERROR_ARGUMENT_OPTION,
				ERROR_ARGUMENT_OPTION_ARGUMENTS,
				ERROR_ARGUMENT_OPTION_ARGUMENTS_OPTION, args[i_string]);
			return (-1);
		}
		char	**dst = ((t_argument *)arguments->arr)[i_argument].dst;
		free(*dst);
		*dst = strdup(args[i_string]);
		if (*dst == NULL)
		{
			fprintf(stderr, "%s: %s: %s: %s\n",
				EXECUTABLE_NAME, LIB_LIBC, FUNC_MALLOC, ERROR_FAILED_ALLOC);
			return (-1);
		}
		i_argument++;
		i_string++;
	}
	if (i_argument < arguments->len)
	{
		fprintf(stderr, "%s: %s: %s: %s: %s\n",
			EXECUTABLE_NAME, ERROR_ARGUMENT, ERROR_ARGUMENT_OPTION,
			ERROR_ARGUMENT_OPTION_ARGUMENTS, ERROR_ARGUMENT_OPTION_ARGUMENTS_TOO_FEW);
		return (-1);
	}
	return ((ssize_t)i_string);
}

static t_parameter	*get_option_parameter(t_option *option, char *arg)
{
	char	*beginning_parameter = strchr(arg, '=');
	if (beginning_parameter == NULL || *(beginning_parameter + 1) == '\0')
	{
		fprintf(stderr, "%s: %s: %s: %s: %s: \"%s\"\n",
			EXECUTABLE_NAME, ERROR_ARGUMENT, ERROR_ARGUMENT_OPTION,
			ERROR_ARGUMENT_OPTION_PARAM, ERROR_ARGUMENT_OPTION_PARAM_TOO_FEW, arg);
		return (NULL);
	}
	beginning_parameter++;
	size_t	i_parameter = 0;
	while (i_parameter < option->parameters.len)
	{
		if (strcmp(((t_parameter *)option->parameters.arr)[i_parameter].name,
			beginning_parameter) == 0)
			return (&((t_parameter *)option->parameters.arr)[i_parameter]);
		i_parameter++;
	}
	fprintf(stderr, "%s: %s: %s: %s: %s: \"%s\"\n",
		EXECUTABLE_NAME, ERROR_ARGUMENT, ERROR_ARGUMENT_OPTION, ERROR_ARGUMENT_OPTION_PARAM,
		ERROR_ARGUMENT_OPTION_PARAM_INVALID, arg);
	return (NULL);
}

static ssize_t	get_i_option(const t_parr *options, char *arg)
{
	size_t	i_option = 0;
	while (i_option < options->len)
	{
		size_t	i_name = 0;
		char	*name = ((t_option *)options->arr)[i_option].names[i_name];
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

static ssize_t	get_option(t_data *data, const t_parr *options, char **args, bool parse_options)
{
	size_t	i_arg = 0;
	ssize_t	i_option = get_i_option(options, args[i_arg]);
	if (i_option == -1)
	{
		fprintf(stderr, "%s: %s: %s: %s: \"%s\"\n",
			EXECUTABLE_NAME, ERROR_ARGUMENT, ERROR_ARGUMENT_OPTION,
			ERROR_ARGUMENT_OPTION_NAME, args[i_arg]);
		return (-1);
	}
	t_option	*option = &((t_option *)options->arr)[i_option];
	t_parameter	*parameter;
	if (option->parameters.len > 0)
	{
		parameter = get_option_parameter(option, args[i_arg]);
		if (parameter == NULL)
			return (-1);
		data->options[i_option] = parameter->parameter;
	}
	else if (has_parameter(args[i_arg]) == 0)
	{
		parameter = NULL;
		data->options[i_option] = PARAM_YES;
	}
	else
	{
		fprintf(stderr, "%s: %s: %s: %s: %s: \"%s\"\n",
			EXECUTABLE_NAME, ERROR_ARGUMENT, ERROR_ARGUMENT_OPTION,
			ERROR_ARGUMENT_OPTION_PARAM, ERROR_ARGUMENT_OPTION_PARAM_TOO_MANY,
			args[i_arg]);
		return (-1);
	}
	t_parr	*arguments;
	if (parameter != NULL && parameter->arguments.len > 0)
		arguments = &parameter->arguments;
	else if (option->parameters.len == 0)
		arguments = &option->arguments;
	else
		arguments = NULL;
	if (arguments != NULL)
		return (get_option_arguments(arguments, &args[i_arg + 1], parse_options));
	return (0);
}

bool	get_arguments(t_data *data, char **args)
{
	const t_parr	options = OPTIONS;
	bool	parse_options = 1, error = 0;
	size_t	i_arg = 0;
	while (args[i_arg] != NULL)
	{
		if (parse_options == 1 && is_option(args[i_arg]) == 1)
		{
			if (strcmp(args[i_arg], OPTION_PARSING_END) == 0)
				parse_options = 0;
			else
			{
				ssize_t	args_to_skip = get_option(data, &options, &args[i_arg],
					parse_options);
				if (args_to_skip == -1)
					return (1);
				i_arg += (size_t)args_to_skip;
			}
		}
		else
		{
			if (((t_file *)data->files.arr)[INPUT_CODE].name == NULL)
			{
				((t_file *)data->files.arr)[INPUT_CODE].name = strdup(args[i_arg]);
				if (((t_file *)data->files.arr)[INPUT_CODE].name == NULL)
				{
					fprintf(stderr, "%s: %s: %s: %s\n",
						EXECUTABLE_NAME, LIB_LIBC, FUNC_MALLOC,
						ERROR_FAILED_ALLOC);
					return (1);
				}
			}
			else
			{
				if (error == 0)
				{
					fprintf(stderr, "%s: %s: %s: ",
						EXECUTABLE_NAME, ERROR_ARGUMENT,
						ERROR_ARGUMENT_TOO_MANY);
					error = 1;
				}
				else
					fprintf(stderr, ", ");
				fprintf(stderr, "\"%s\"", args[i_arg]);
			}
		}
		i_arg++;
	}
	if (error == 1)
		fprintf(stderr, "\n");
	return (error);
}
