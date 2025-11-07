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
#define REQUIREMENT_MASK	3
#define PERMISSION_MASK		7

// Bit positions
#define REQUIREMENT_POS	0
#define PERMISSION_POS	2

// Function fopen modes
#define FOPEN_READ_MODE		"r"
#define FOPEN_WRITE_MODE	"w"

/* ----- ENUMERATIONS ----- */

// Requirement
enum
{
	MANDATORY,
	OPTIONAL,
	UNUSED
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
	char	*name;
	FILE	*stream;
	uint8_t	info;
}	t_file;

/* ----- PROTOTYPES ----- */

// file/
//	open.c
bool	file_open(t_file *file, char *mode);
//	get_next_line.c
bool	file_get_next_line(t_file *file, char **line);
//	close.c
void	file_close(t_file *file);
//	free.c
void	file_free(void *file);
