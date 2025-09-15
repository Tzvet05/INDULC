#pragma once

/* ----- INCLUDES ----- */

#include <stdbool.h>

/* ----- TYPES DECLARATIONS ----- */

typedef struct	data	t_data;

/* ----- ENUMERATIONS ----- */

// Files
enum
{
	INFILE_PROGRAM,
	OUTFILE_PROGRAM,
	INFILE_ISA
};

/* ----- PROTOTYPES ----- */

// files/
//	files.c
void	close_files(t_data* data);
bool	check_files(t_data* data);
