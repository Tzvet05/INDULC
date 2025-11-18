#pragma once

/* ----- INCLUDES ----- */

#include <stdbool.h>
#include "parr.h"
#include "files.h"

/* ----- MACROS ----- */

// Default options
#define DEFAULT_OPTIONS	(t_option_parameter []){PARAM_NO, PARAM_NO, PARAM_YES, PARAM_NO, PARAM_NO, PARAM_NO, PARAM_NO, PARAM_NO, PARAM_NO, PARAM_ALL}

// Options
#define OPTION_PARSING_END	"--"
#define OPTIONS	\
{\
	.len = 10, \
	.obj_size = sizeof(t_option), \
	.arr = (t_option [])\
	{\
		{\
			.names = (char *[]){"--version", NULL}\
		}, \
		{\
			.names = (char *[]){"--help", "-h", NULL}\
		}, \
		{\
			.names = (char *[]){"--macro-warnings", "-mw", NULL}, \
			.parameters = \
			{\
				.len = 2, \
				.obj_size = sizeof(t_parameter), \
				.arr = (t_parameter [])\
				{\
					{\
						.name = "yes", \
						.parameter = PARAM_YES\
					}, \
					{\
						.name = "no", \
						.parameter = PARAM_NO\
					}\
				}\
			}\
		}, \
		{\
			.names = (char *[]){"--isa-only", "-j", NULL}, \
			.parameters = \
			{\
				.len = 2, \
				.obj_size = sizeof(t_parameter), \
				.arr = (t_parameter [])\
				{\
					{\
						.name = "yes", \
						.parameter = PARAM_YES\
					}, \
					{\
						.name = "no", \
						.parameter = PARAM_NO\
					}\
				}\
			}\
		}, \
		{\
			.names = (char *[]){"--syntax-only", "-s", NULL}, \
			.parameters = \
			{\
				.len = 2, \
				.obj_size = sizeof(t_parameter), \
				.arr = (t_parameter [])\
				{\
					{\
						.name = "yes", \
						.parameter = PARAM_YES\
					}, \
					{\
						.name = "no", \
						.parameter = PARAM_NO\
					}\
				}\
			}\
		}, \
		{\
			.names = (char *[]){"--isa-file", "-i", NULL}, \
			.arguments = \
			{\
				.len = 2, \
				.obj_size = sizeof(t_argument), \
				.arr = (t_argument [])\
				{\
					{\
						.dst = &((t_file *)data->files.arr)[INPUT_ISA].info, \
						.size = sizeof(uint8_t), \
						.src = &(uint8_t){SET_REQUIREMENT(MANDATORY) | SET_PERMISSION(READ)}, \
						.type = CPY\
					}, \
					{\
						.dst = &((t_file *)data->files.arr)[INPUT_ISA].name\
					}\
				}\
			}\
		}, \
		{\
			.names = (char *[]){"--signals-file", "-si", NULL}, \
			.arguments = \
			{\
				.len = 2, \
				.obj_size = sizeof(t_argument), \
				.arr = (t_argument [])\
				{\
					{\
						.dst = &((t_file *)data->files.arr)[INPUT_SIGNALS].info, \
						.size = sizeof(uint8_t), \
						.src = &(uint8_t){SET_REQUIREMENT(MANDATORY) | SET_PERMISSION(READ)}, \
						.type = CPY\
					}, \
					{\
						.dst = &((t_file *)data->files.arr)[INPUT_SIGNALS].name\
					}\
				}\
			}\
		}, \
		{\
			.names = (char *[]){"--machine-code-output", "-mo", NULL}, \
			.parameters = \
			{\
				.len = 3, \
				.obj_size = sizeof(t_parameter), \
				.arr = (t_parameter [])\
				{\
					{\
						.name = "bin", \
						.parameter = PARAM_BIN, \
						.arguments = \
						{\
							.len = 2, \
							.obj_size = sizeof(t_argument), \
							.arr = (t_argument [])\
							{\
								{\
									.dst = &((t_file *)data->files.arr)[OUTPUT_MACHINE_CODE].info, \
									.size = sizeof(uint8_t), \
									.src = &(uint8_t){SET_REQUIREMENT(OPTIONAL) | SET_PERMISSION(WRITE) | SET_INFO(PREPEND)}, \
									.type = CPY\
								}, \
								{\
									.dst = &((t_file *)data->files.arr)[OUTPUT_MACHINE_CODE].name, \
									.size = strlen(TAIL_OUTPUT_MACHINE_CODE_BIN) + 1, \
									.src = TAIL_OUTPUT_MACHINE_CODE_BIN, \
									.type = DUP\
								}\
							}\
						}\
					}, \
					{\
						.name = "ascii", \
						.parameter = PARAM_ASCII, \
						.arguments = \
						{\
							.len = 2, \
							.obj_size = sizeof(t_argument), \
							.arr = (t_argument [])\
							{\
								{\
									.dst = &((t_file *)data->files.arr)[OUTPUT_MACHINE_CODE].info, \
									.size = sizeof(uint8_t), \
									.src = &(uint8_t){SET_REQUIREMENT(OPTIONAL) | SET_PERMISSION(WRITE) | SET_INFO(PREPEND)}, \
									.type = CPY\
								}, \
								{\
									.dst = &((t_file *)data->files.arr)[OUTPUT_MACHINE_CODE].name, \
									.size = strlen(TAIL_OUTPUT_MACHINE_CODE_TXT) + 1, \
									.src = TAIL_OUTPUT_MACHINE_CODE_TXT, \
									.type = DUP\
								}\
							}\
						}\
					}, \
					{\
						.name = "no", \
						.parameter = PARAM_NO, \
						.arguments = \
						{\
							.len = 1, \
							.obj_size = sizeof(t_argument), \
							.arr = (t_argument [])\
							{\
								{\
									.dst = &((t_file *)data->files.arr)[OUTPUT_MACHINE_CODE].info, \
									.size = sizeof(uint8_t), \
									.src = &(uint8_t){SET_REQUIREMENT(UNUSED)}, \
									.type = CPY\
								}\
							}\
						}\
					}\
				}\
			}\
		}, \
		{\
			.names = (char *[]){"--json-output", "-jo", NULL}, \
			.parameters = \
			{\
				.len = 3, \
				.obj_size = sizeof(t_parameter), \
				.arr = (t_parameter [])\
				{\
					{\
						.name = "compact", \
						.parameter = PARAM_COMPACT, \
						.arguments = \
						{\
							.len = 2, \
							.obj_size = sizeof(t_argument), \
							.arr = (t_argument [])\
							{\
								{\
									.dst = &((t_file *)data->files.arr)[OUTPUT_JSON].info, \
									.size = sizeof(uint8_t), \
									.src = &(uint8_t){SET_REQUIREMENT(OPTIONAL) | SET_PERMISSION(WRITE) | SET_INFO(PREPEND)}, \
									.type = CPY\
								}, \
								{\
									.dst = &((t_file *)data->files.arr)[OUTPUT_JSON].name, \
									.size = strlen(TAIL_OUTPUT_JSON) + 1, \
									.src = TAIL_OUTPUT_JSON, \
									.type = DUP\
								}\
							}\
						}\
					}, \
					{\
						.name = "format", \
						.parameter = PARAM_FORMAT, \
						.arguments = \
						{\
							.len = 2, \
							.obj_size = sizeof(t_argument), \
							.arr = (t_argument [])\
							{\
								{\
									.dst = &((t_file *)data->files.arr)[OUTPUT_JSON].info, \
									.size = sizeof(uint8_t), \
									.src = &(uint8_t){SET_REQUIREMENT(OPTIONAL) | SET_PERMISSION(WRITE) | SET_INFO(PREPEND)}, \
									.type = CPY\
								}, \
								{\
									.dst = &((t_file *)data->files.arr)[OUTPUT_JSON].name, \
									.size = strlen(TAIL_OUTPUT_JSON) + 1, \
									.src = TAIL_OUTPUT_JSON, \
									.type = DUP\
								}\
							}\
						}\
					}, \
					{\
						.name = "no", \
						.parameter = PARAM_NO, \
						.arguments = \
						{\
							.len = 1, \
							.obj_size = sizeof(t_argument), \
							.arr = (t_argument [])\
							{\
								{\
									.dst = &((t_file *)data->files.arr)[OUTPUT_JSON].info, \
									.size = sizeof(uint8_t), \
									.src = &(uint8_t){SET_REQUIREMENT(UNUSED)}, \
									.type = CPY\
								}\
							}\
						}\
					}\
				}\
			}\
		}, \
		{\
			.names = (char *[]){"--string-output", "-o", NULL}, \
			.parameters = \
			{\
				.len = 4, \
				.obj_size = sizeof(t_parameter), \
				.arr = (t_parameter [])\
				{\
					{\
						.name = "all", \
						.parameter = PARAM_ALL, \
						.arguments = \
						{\
							.len = 2, \
							.obj_size = sizeof(t_argument), \
							.arr = (t_argument [])\
							{\
								{\
									.dst = &((t_file *)data->files.arr)[OUTPUT_STRING].info, \
									.size = sizeof(uint8_t), \
									.src = &(uint8_t){SET_REQUIREMENT(OPTIONAL) | SET_PERMISSION(WRITE) | SET_INFO(PREPEND)}, \
									.type = CPY\
								}, \
								{\
									.dst = &((t_file *)data->files.arr)[OUTPUT_STRING].name, \
									.size = strlen(TAIL_OUTPUT_STRING) + 1, \
									.src = TAIL_OUTPUT_STRING, \
									.type = DUP\
								}\
							}\
						}\
					}, \
					{\
						.name = "file", \
						.parameter = PARAM_FILE, \
						.arguments = \
						{\
							.len = 2, \
							.obj_size = sizeof(t_argument), \
							.arr = (t_argument [])\
							{\
								{\
									.dst = &((t_file *)data->files.arr)[OUTPUT_STRING].info, \
									.size = sizeof(uint8_t), \
									.src = &(uint8_t){SET_REQUIREMENT(OPTIONAL) | SET_PERMISSION(WRITE) | SET_INFO(PREPEND)}, \
									.type = CPY\
								}, \
								{\
									.dst = &((t_file *)data->files.arr)[OUTPUT_STRING].name, \
									.size = strlen(TAIL_OUTPUT_STRING) + 1, \
									.src = TAIL_OUTPUT_STRING, \
									.type = DUP\
								}\
							}\
						}\
					}, \
					{\
						.name = "terminal", \
						.parameter = PARAM_TERMINAL, \
						.arguments = \
						{\
							.len = 1, \
							.obj_size = sizeof(t_argument), \
							.arr = (t_argument [])\
							{\
								{\
									.dst = &((t_file *)data->files.arr)[OUTPUT_STRING].info, \
									.size = sizeof(uint8_t), \
									.src = &(uint8_t){SET_REQUIREMENT(UNUSED)}, \
									.type = CPY\
								}\
							}\
						}\
					}, \
					{\
						.name = "no", \
						.parameter = PARAM_NO, \
						.arguments = \
						{\
							.len = 1, \
							.obj_size = sizeof(t_argument), \
							.arr = (t_argument [])\
							{\
								{\
									.dst = &((t_file *)data->files.arr)[OUTPUT_STRING].info, \
									.size = sizeof(uint8_t), \
									.src = &(uint8_t){SET_REQUIREMENT(UNUSED)}, \
									.type = CPY\
								}\
							}\
						}\
					}\
				}\
			}\
		}\
	}\
}

// Option outputs
#define EXECUTABLE_VERSION	"2.2.0"
#define EXECUTABLE_HELP		"Usage: ./indulc {input}\n\
	{input} is the mandatory input file from which the INDUL code is read.\n\
	The mandatory default input file from which the ISA is read is named \"isa.json\".\n\
	The default input file from which the Factorio signals are read is named \"signals.json\".\n\
	The optional default output file in which the blueprint string can be written is named \"[input]_string.txt\", where \"[input]\" is the name of the input file.\n\
	The optional output file in which the assembled machine code can be written is named \"[input]_machine_code.bin\" or \"[input]_machine_code.txt\", where \"[input]\" is the name of the input file.\n\
	The optional output file in which the Json blueprint object can be written is named \"[input]_blueprint.json\", where \"[input]\" is the name of the input file.\n\
\n\
	Options can be added at any point in the arguments, except among an option's arguments.\n\
	The \"--\" argument can be used to indicate the end of option parsing. Any argument following it will be treated as a regular argument rather than as an option.\n\
	The default parameters and arguments are indicated with [ ].\n\
	Option arguments are indicated with { }.\n\
	The available options are :\n\
		-h|--help					Show this message.\n\
		--version					Show INDULC's version.\n\
		-mw|--macro-warnings=no|[yes]			Display macro-related warnings.\n\
		-j|--isa-only=[no]|yes				Only check the ISA's syntax.\n\
		-s|--syntax-only=[no]|yes			Only check the code's syntax.\n\
		-i|--isa-file {file}|[isa.json]			Indicate ISA file to read from.\n\
		-si|--signals-file {file}|[signals.json]	Indicate Factorio signals file to read from.\n\
		-mo|--machine-code-output=[no]|bin|ascii	Output machine code as raw binary or ASCII characters.\n\
		-jo|--json-output=[no]|compact|format		Output Json blueprint object in a compact or formatted manner.\n\
		-o|--string-output=no|terminal|file|[all]	Output blueprint string in terminal, file or both.\n\
\n\
Refer to the README at the root of the repository for more informations and details.\n\
\n\
INDULC is licensed under the MIT license.\n\
GitHub repository available at : github.com/Tzvet05/INDULC. All contributions are welcome."

/* ----- ENUMERATIONS ----- */

// Option indexes
enum
{
	OPTION_VERSION,
	OPTION_HELP,
	OPTION_MACRO_WARNINGS,
	OPTION_ISA_ONLY,
	OPTION_SYNTAX_ONLY,
	OPTION_ISA_FILE,
	OPTION_SIGNALS_FILE,
	OPTION_MACHINE_CODE_OUTPUT,
	OPTION_JSON_OUTPUT,
	OPTION_STRING_OUTPUT
};

// Option parameters
typedef enum	option_parameter
{
	PARAM_NO,
	PARAM_YES,
	PARAM_ALL,
	PARAM_BIN,
	PARAM_ASCII,
	PARAM_COMPACT,
	PARAM_FORMAT,
	PARAM_TERMINAL,
	PARAM_FILE
}	t_option_parameter;

// Argument copy type
typedef enum	cpy_type
{
	CPY,
	DUP
}	t_cpy_type;

/* ----- TYPES DECLARATIONS ----- */

typedef struct	data	t_data;

/* ----- STRUCTURES ----- */

// Option/parameter argument
typedef struct	argument
{
	void		*dst;//	Pointer to the object to substitute
	size_t		size;//	Size of the object to subtitute
	void		*src;//	Pointer to the substituting object
	t_cpy_type	type;//	Type of copying
}	t_argument;

// Option parameter
typedef struct	parameter
{
	char			*name;//	Name of the parameter
	t_option_parameter	parameter;//	Parameter
	t_parr			arguments;//	Array of arguments (overwrites the default option arguments)
}	t_parameter;

// Option
typedef struct	option
{
	char	**names;//	Array of option names
	t_parr	parameters;//	Array of option parameters
	t_parr	arguments;//	Array of arguments (overwritten by the parameter arguments)
}	t_option;

/* ----- PROTOTYPES ----- */

// arguments/
//	get.c
bool	get_arguments(t_data *data, char **args);
//	check.c
bool	check_arguments(t_data *data);
//	exec_options.c
bool	exec_options(t_option_parameter *options, bool *error);
