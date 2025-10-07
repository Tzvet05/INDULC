#pragma once

/* ----- INCLUDES ----- */

#include <stdbool.h>
#include "parr.h"
#include "files.h"

/* ----- MACROS ----- */

// Default file names
#define DEFAULT_OUTFILE_PROGRAM	"a.out"
#define DEFAULT_INFILE_ISA	"isa.json"

// Default options
#define DEFAULT_OPTIONS	(t_option_parameter[]){NO, NO, NO, YES, NO, NO, NO, NO}

// Options
#define OPTION_PARSING_END	"--"
#define OPTIONS	\
(const t_parr){\
	.len = 8, \
	.obj_size = sizeof(t_option), \
	.arr = (t_option[])\
	{\
		(t_option){\
			.names = (char*[]){"--version", NULL}\
		}, \
		(t_option){\
			.names = (char*[]){"--help", "-h", NULL}\
		}, \
		(t_option){\
			.names = (char*[]){"--output-chars", "-c", NULL}, \
			.parameters = \
			(t_parr){\
				.len = 2, \
				.obj_size = sizeof(t_parameter), \
				.arr = (t_parameter[])\
				{\
					(t_parameter){\
						.name = "yes", \
						.parameter = YES\
					}, \
					(t_parameter){\
						.name = "no", \
						.parameter = NO\
					}\
				}\
			}\
		}, \
		(t_option){\
			.names = (char*[]){"--macro-warnings", "-m", NULL}, \
			.parameters = \
			(t_parr){\
				.len = 2, \
				.obj_size = sizeof(t_parameter), \
				.arr = (t_parameter[])\
				{\
					(t_parameter){\
						.name = "yes", \
						.parameter = YES\
					}, \
					(t_parameter){\
						.name = "no", \
						.parameter = NO\
					}\
				}\
			}\
		}, \
		(t_option){\
			.names = (char*[]){"--isa-only", "-j", NULL}, \
			.parameters = \
			(t_parr){\
				.len = 2, \
				.obj_size = sizeof(t_parameter), \
				.arr = (t_parameter[])\
				{\
					(t_parameter){\
						.name = "yes", \
						.parameter = YES\
					}, \
					(t_parameter){\
						.name = "no", \
						.parameter = NO\
					}\
				}\
			}\
		}, \
		(t_option){\
			.names = (char*[]){"--syntax-only", "-s", NULL}, \
			.parameters = \
			(t_parr){\
				.len = 2, \
				.obj_size = sizeof(t_parameter), \
				.arr = (t_parameter[])\
				{\
					(t_parameter){\
						.name = "yes", \
						.parameter = YES\
					}, \
					(t_parameter){\
						.name = "no", \
						.parameter = NO\
					}\
				}\
			}\
		}, \
		(t_option){\
			.names = (char*[]){"--output-file", "-o", NULL}, \
			.arguments = \
			(t_parr){\
				.len = 1, \
				.obj_size = sizeof(char**), \
				.arr = (char**[]){&((t_file *)data->files.arr)[OUTFILE_PROGRAM].name}\
			}\
		}, \
		(t_option){\
			.names = (char*[]){"--isa-file", "-i", NULL}, \
			.arguments = \
			(t_parr){\
				.len = 1, \
				.obj_size = sizeof(char**), \
				.arr = (char**[]){&((t_file *)data->files.arr)[INFILE_ISA].name}\
			}\
		}\
	}\
}

// Option outputs
#define EXECUTABLE_VERSION	"2.2.0"
#define EXECUTABLE_HELP		"Usage: ./indulc {program input file}\n\
	{program input file} is the input file from which the INDUL code is read. INDULC must have reading permissions for it. This argument is mandatory.\n\
	The default output file in which the assembled machine code is written is named \"a.out\". If it does not exist, INDULC will create it. If it already exists, INDULC must have writing permissions for it.\n\
	The default input file from which the ISA is read is named \"isa.json\". INDULC must have reading permissions for it.\n\
\n\
	Options can be added at any point in the arguments, except among an option's arguments.\n\
	The \"--\" argument can be used to indicate the end of option parsing. Any argument following it will be treated as a regular argument rather than as an option.\n\
	The default parameters and arguments are indicated with [ ].\n\
	Option arguments are indicated with { }.\n\
	The available options are :\n\
		-h|--help			Show this message.\n\
		--version			Show INDULC's version.\n\
		-c|--output-chars=[no]|yes	Write machine code as ASCII characters rather than raw binary. Useful for debugging.\n\
		-m|--macro-warnings=no|[yes]	Display macro-related warnings.\n\
		-j|--isa-only=[no]|yes		Only check the ISA's syntax.\n\
		-s|--syntax-only=[no]|yes	Only check the code's syntax.\n\
		-o|--output-file {file}|[a.out]	Indicate output file to write to.\n\
		-i|--isa-file {file}|[isa.json]	Indicate ISA file to read from.\n\
\n\
Refer to the README at the root of the repository for more informations.\n\
\n\
GitHub repository available at : github.com/Tzvet05/INDULC\n\
Programmed by Tzvet for their Industrious CPUs, a series of RISC CPUs implemented in Factorio."

/* ----- ENUMERATIONS ----- */

// Option indexes
enum	option_index
{
	OPTION_VERSION,
	OPTION_HELP,
	OPTION_OUTPUT_CHARS,
	OPTION_MACRO_WARNINGS,
	OPTION_ISA_ONLY,
	OPTION_SYNTAX_ONLY,
	OPTION_OUTPUT_FILE,
	OPTION_ISA_FILE
};

/* ----- TYPES DECLARATIONS ----- */

typedef struct	file	t_file;
typedef struct	data	t_data;

// Option parameters
typedef enum	option_parameter
{
	NO,
	YES
}	t_option_parameter;

/* ----- STRUCTURES ----- */

// Option parameter
typedef struct parameter
{
	char*			name;//		Name of the parameter
	t_option_parameter	parameter;//	Parameter
}	t_parameter;

// Option
typedef struct option
{
	char**	names;//	Array of option names
	t_parr	parameters;//	Array of option parameters
	t_parr	arguments;//	Array of pointers to the strings to subsitute
}	t_option;

/* ----- PROTOTYPES ----- */

// arguments/
//	get_arguments.c
bool	get_arguments(t_data* data, char** args);
//	check_arguments.c
bool	check_arguments(t_data* data);
//	exec_options.c
bool	exec_options(t_option_parameter* options, bool* error);
//	arguments_utils.c
bool	is_option(char* str);
bool	has_parameter(char* str);
