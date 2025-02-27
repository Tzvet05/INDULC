#pragma once

/* ----- INCLUDES ----- */

#include <stdio.h>
#include <stdbool.h>

/* ----- MACROS ----- */

// fopen() modes
#define FOPEN_READ_MODE		"r"
#define FOPEN_WRITE_MODE	"w"

/* ----- STRUCTURES ----- */

// File
typedef struct file
{
	char*	name;
	FILE*	stream;
}	t_file;

/* ----- PROTOTYPES ----- */

bool	open_file(t_file* file, char* mode);
void	close_file(t_file* file);
bool	get_next_line(t_file* file, char** line_ptr);
