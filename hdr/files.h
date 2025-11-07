#pragma once

/* ----- INCLUDES ----- */

#include <stdbool.h>

/* ----- MACROS ----- */

// Default file names
#define DEFAULT_INFILE_ISA			"isa.json"
#define DEFAULT_INFILE_SIGNALS			"signals.json"
#define DEFAULT_OUTFILE_MACHINE_CODE_BIN	"machine_code.bin"
#define DEFAULT_OUTFILE_MACHINE_CODE_TXT	"machine_code.txt"
#define DEFAULT_OUTFILE_JSON			"blueprint.json"
#define DEFAULT_OUTFILE_STRING			"string.txt"

// Default files
#define DEFAULT_FILES	\
{\
	.len = 6, \
	.obj_size = sizeof(t_file), \
	.arr = (t_file [])\
	{\
		{\
			.info = SET_REQUIREMENT(MANDATORY) | SET_PERMISSION(READ)\
		}, \
		{\
			.name = DEFAULT_INFILE_ISA, \
			.info = SET_REQUIREMENT(MANDATORY) | SET_PERMISSION(READ)\
		}, \
		{\
			.name = DEFAULT_INFILE_SIGNALS, \
			.info = SET_REQUIREMENT(MANDATORY) | SET_PERMISSION(READ)\
		}, \
		{\
			.info = SET_REQUIREMENT(UNUSED)\
		}, \
		{\
			.info = SET_REQUIREMENT(UNUSED)\
		}, \
		{\
			.name = DEFAULT_OUTFILE_STRING, \
			.info = SET_REQUIREMENT(OPTIONAL) | SET_PERMISSION(WRITE)\
		}\
	}\
}

/* ----- ENUMERATIONS ----- */

// Files
enum
{
	INFILE_CODE,
	INFILE_ISA,
	INFILE_SIGNALS,
	OUTFILE_MACHINE_CODE,
	OUTFILE_JSON,
	OUTFILE_STRING
};

/* ----- TYPES DECLARATIONS ----- */

typedef struct	data	t_data;

/* ----- PROTOTYPES ----- */

// files/
//	check.c
bool	check_files(t_data *data);
//	init.c
bool	alloc_files(t_data *data);
bool	init_files(t_data *data);
