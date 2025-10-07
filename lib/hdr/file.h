#pragma once

/* ----- INCLUDES ----- */

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

/* ----- MACROS ----- */

// Function macros
#define SET_REQUIREMENT(requirement)		((requirement & REQUIREMENT_MASK) << REQUIREMENT_POS)
#define SET_PERMISSION(permission)		((permission & PERMISSION_MASK) << PERMISSION_POS)
#define GET_REQUIREMENT(info)			((info >> REQUIREMENT_POS) & REQUIREMENT_MASK)
#define GET_PERMISSION(info, permission)	((info >> PERMISSION_POS) & PERMISSION_MASK & permission)

// Bit masks
#define REQUIREMENT_MASK	1
#define PERMISSION_MASK		7

// Bit positions
#define REQUIREMENT_POS	0
#define PERMISSION_POS	1

// fopen() modes
#define FOPEN_READ_MODE		"r"
#define FOPEN_WRITE_MODE	"w"

/* ----- ENUMERATIONS ----- */

// Requirement
enum
{
	MANDATORY,
	OPTIONAL
};

// Permissions
enum
{
	READ =	(1 << 0),
	WRITE =	(1 << 1),
	EXEC =	(1 << 2)
};

/* ----- STRUCTURES ----- */

// File
typedef struct file
{
	char*	name;
	FILE*	stream;
	uint8_t	info;
}	t_file;

/* ----- PROTOTYPES ----- */

bool	open_file(t_file* file, char* mode);
void	close_file(t_file* file);
bool	get_next_line(t_file* file, char** line);
