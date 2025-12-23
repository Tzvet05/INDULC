#pragma once

/* ----- INCLUDES ----- */

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

/* ----- MACROS ----- */

// Function macros
#define SET_REQUIREMENT(requirement)	((requirement & MASK_REQUIREMENT) << POS_REQUIREMENT)
#define SET_PERMISSION(permission)	((permission & MASK_PERMISSION) << POS_PERMISSION)
#define SET_INFO(info)			((info & MASK_INFO) << POS_INFO)
#define GET_REQUIREMENT(info)		((info >> POS_REQUIREMENT) & MASK_REQUIREMENT)
#define GET_PERMISSION(info, mask)	((info >> POS_PERMISSION) & MASK_PERMISSION & mask)
#define GET_INFO(info, mask)		((info >> POS_INFO) & MASK_INFO & mask)

// Bit masks
#define MASK_REQUIREMENT	3
#define MASK_PERMISSION		7
#define MASK_INFO		7

// Bit positions
#define POS_REQUIREMENT	0
#define POS_PERMISSION	2
#define POS_INFO	5

// Function fopen modes
#define FOPEN_MODE_READ		"r"
#define FOPEN_MODE_WRITE	"w"

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

/* ----- TYPES DECLARATIONS ----- */

typedef struct	pstr	pstr_t;

/* ----- STRUCTURES ----- */

// File
typedef struct	file
{
	char	*name;
	FILE	*stream;
	uint8_t	info;
}	file_t;

/* ----- PROTOTYPES ----- */

// file/
//	open.c
bool	file_open(file_t *file, char *mode);
//	get_name.c
pstr_t	file_get_name(char *path);
//	get_next_line.c
bool	file_get_next_line(file_t *file, char **line);
//	close.c
void	file_close(file_t *file);
//	free.c
void	file_free(void *file);
