#pragma once

/* ----- INCLUDES ----- */

#include "data.h"

/* ----- ENUMERATIONS ----- */

// Files
enum
{
	INFILE_PROGRAM = 0,
	OUTFILE_PROGRAM,
	INFILE_ISA
};

/* ----- MACROS ----- */

// Default file names
#define DEFAULT_OUTFILE_PROGRAM	"a.out"
#define DEFAULT_INFILE_ISA	"isa.json"

/* ----- PROTOTYPES ----- */

// files/
//	files.c
void	close_files(t_data* data);
void	init_filenames(t_data* data, char** file_names);
bool	check_files(t_data* data);
