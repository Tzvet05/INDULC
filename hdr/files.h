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

/* ----- PROTOTYPES ----- */

// files/
//	files.c
void	close_files(t_data* data);
bool	check_files(t_data* data);
