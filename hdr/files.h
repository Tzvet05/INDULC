#pragma once

/* ----- INCLUDES ----- */

#include <stdbool.h>

/* ----- MACROS ----- */

// Default files
#define DEFAULT_FILES	\
(t_parr){\
	.len = 3, \
	.obj_size = sizeof(t_file), \
	.arr = (t_file[])\
	{\
		(t_file){\
			.info = SET_REQUIREMENT(MANDATORY) | SET_PERMISSION(READ)\
		},\
		(t_file){\
			.name = DEFAULT_OUTFILE_PROGRAM, \
			.info = SET_REQUIREMENT(OPTIONAL) | SET_PERMISSION(WRITE)\
		},\
		(t_file){\
			.name = DEFAULT_INFILE_ISA, \
			.info = SET_REQUIREMENT(MANDATORY) | SET_PERMISSION(READ)\
		}\
	}\
}

/* ----- ENUMERATIONS ----- */

// Files
enum
{
	INFILE_PROGRAM,
	OUTFILE_PROGRAM,
	INFILE_ISA
};

/* ----- TYPES DECLARATIONS ----- */

typedef struct	data	t_data;

/* ----- PROTOTYPES ----- */

// files/
//	files.c
void	close_files(t_data* data);
bool	check_files(t_data* data);
