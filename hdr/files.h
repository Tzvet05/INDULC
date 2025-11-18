#pragma once

/* ----- INCLUDES ----- */

#include <stdbool.h>

/* ----- MACROS ----- */

// Default file names
#define DEFAULT_INPUT_ISA	"data/isa.json"
#define DEFAULT_INPUT_SIGNALS	"data/signals.json"

// File tails
#define TAIL_OUTPUT_MACHINE_CODE_BIN	"_machine_code.bin"
#define TAIL_OUTPUT_MACHINE_CODE_TXT	"_machine_code.txt"
#define TAIL_OUTPUT_JSON		"_blueprint.json"
#define TAIL_OUTPUT_STRING		"_string.txt"

// Number of files
#define N_FILES	6

// Default files
#define DEFAULT_FILES	\
{\
	.len = N_FILES, \
	.obj_size = sizeof(t_file), \
	.arr = (t_file [])\
	{\
		{\
			.info = SET_REQUIREMENT(MANDATORY) | SET_PERMISSION(READ)\
		}, \
		{\
			.name = DEFAULT_INPUT_ISA, \
			.info = SET_REQUIREMENT(MANDATORY) | SET_PERMISSION(READ)\
		}, \
		{\
			.name = DEFAULT_INPUT_SIGNALS, \
			.info = SET_REQUIREMENT(MANDATORY) | SET_PERMISSION(READ)\
		}, \
		{\
			.info = SET_REQUIREMENT(UNUSED)\
		}, \
		{\
			.info = SET_REQUIREMENT(UNUSED)\
		}, \
		{\
			.name = TAIL_OUTPUT_STRING, \
			.info = SET_REQUIREMENT(OPTIONAL) | SET_PERMISSION(WRITE) | SET_INFO(PREPEND)\
		}\
	}\
}

/* ----- ENUMERATIONS ----- */

// File info
enum
{
	PREPEND =	(1 << 0)
};

// Files
enum
{
	INPUT_CODE,
	INPUT_ISA,
	INPUT_SIGNALS,
	OUTPUT_MACHINE_CODE,
	OUTPUT_JSON,
	OUTPUT_STRING
};

/* ----- TYPES DECLARATIONS ----- */

typedef struct	data	t_data;

/* ----- PROTOTYPES ----- */

// files/
//	check.c
bool	check_files(t_data *data);
//	init.c
bool	init_files(t_data *data);
//	free.c
void	free_files(t_parr *files);
