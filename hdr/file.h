#pragma once

/* ----- INCLUDES ----- */

#include <stdio.h>

/* ----- ENUMERATIONS ----- */

// Files
enum
{
	INFILE_PROGRAM = 0,
	OUTFILE_PROGRAM,
	INFILE_ISA
};

/* ----- MACROS ----- */

#define DEFAULT_OUTFILE_PROGRAM	"a.out"
#define DEFAULT_INFILE_ISA	"isa.json"

/* ----- STRUCTURES ----- */

// File
typedef struct file
{
	char*	name;
	FILE*	stream;
}	t_file;
