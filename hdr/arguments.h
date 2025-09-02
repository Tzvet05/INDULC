#pragma once

/* ----- INCLUDES ----- */

#include <stdbool.h>
#include "data.h"
#include "option.h"

/* ----- MACROS ----- */

// Default file names
#define DEFAULT_OUTFILE_PROGRAM	"a.out"
#define DEFAULT_INFILE_ISA	"isa.json"
#define DEFAULT_FILES		(const char* const[]){DEFAULT_OUTFILE_PROGRAM, DEFAULT_INFILE_ISA}

// Option strings
#define OPTIONS	\
(const t_parr){\
	.len = 4, \
	.obj_size = sizeof(t_option), \
	.arr = (t_option[])\
	{\
		(t_option){\
			.names = \
			(char*[]){\
				"--version", NULL\
			}, \
			.values = NULL\
		}, \
		(t_option){\
			.names = \
			(char*[]){\
				"--help", "-h", NULL\
			}, \
			.values = NULL\
		}, \
		(t_option){\
			.names = \
			(char*[]){\
				"--output-chars", "-c", NULL\
			}, \
			.values = \
			(char*[]){\
				"no", "yes"\
			}\
		}, \
		(t_option){\
			.names = \
			(char*[]){\
				"--mute-macro-warnings", "-m", NULL\
			}, \
			.values = \
			(char*[]){\
				"no", "yes"\
			}\
		}\
	}\
}

// Option bits
#define OPTION_VERSION			(1 << 0)
#define OPTION_HELP			(1 << 1)
#define OPTION_OUTPUT_CHARS		(1 << 2)
#define OPTION_MUTE_MACRO_WARNINGS	(1 << 3)

// Option outputs
#define EXECUTABLE_VERSION	"2.1.0"
#define EXECUTABLE_HELP		"Usage: ./indulc [program infile] ([program outfile]) ([isa infile])\n\
	[program infile] is the input file from which the INDUL code is read. INDULC must have reading permissions on it. This argument is mandatory.\n\
	[program outfile] is the output file in which the machine code is written. If it exists, INDULC must have writing permissions on it and will overwrite it, otherwise, INDULC will create it. This argument is optional and will default to \"a.out\" if not provided.\n\
	[isa infile] is the input file from which the ISA used by INDULC is read. If it does not exist, or if INDULC does not have reding permissions on it, INDULC will report an error. This argument is optional and will default to \"isa.json\" if not provided.\n\
\n\
	Options can be added at any point in the arguments.\n\
	The \"--\" argument can be used to indicate the end of option parsing. Any argument following it will be treated as a regular argument rather than as an option.\n\
	The default options are indicated with [ ].\n\
	The available options are :\n\
		-h --help					Show this message.\n\
		--version					Show INDULC's version.\n\
		-c --output-chars		=[no]|yes	Write machine code as ASCII characters rather than raw binary. Useful for debugging.\n\
		-m --mute-macro-warnings	=no|[yes]	Mute macro-related warnings.\n\
\n\
See the README at the root of the repository for more informations.\n\
\n\
GitHub repository available at : github.com/Tzvet05/INDULC\n\
Programmed by Tzvet for their Industrious CPUs, a series of RISC CPUs implemented in Factorio."

/* ----- PROTOTYPES ----- */

// arguments/
//	get_arguments.c
bool	get_arguments(t_data* data, char** args);
//	exec_options.c
bool	exec_options(uint8_t options);
