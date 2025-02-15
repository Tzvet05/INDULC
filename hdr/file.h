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

// Default file names
#define DEFAULT_OUTFILE_PROGRAM	"a.out"
#define DEFAULT_INFILE_ISA	"isa.json"

// fopen() modes
#define READ_MODE	"r"
#define WRITE_MODE	"w"

/* ----- STRUCTURES ----- */

// File
typedef struct file
{
	char*	name;
	FILE*	stream;
}	t_file;
