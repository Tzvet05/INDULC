#pragma once

/* ----- INCLUDES ----- */

#include <sys/types.h>
#include "cJSON.h"
#include "parr.h"

/* ----- MACROS ----- */

// Json signals key fields
#define JSON_TYPES		"types"
#define JSON_QUALITIES		"qualities"
#define JSON_SIGNALS		"signals"
#define JSON_SIGNAL_NAME	"name"
#define JSON_SIGNAL_TYPE	"type"

/* ----- ENUMERATIONS ----- */

enum
{
	LABEL,
	DESCRIPTION
};

/* ----- TYPES DECLARATIONS ----- */

typedef struct	data	t_data;

/* ----- STRUCTURES ----- */

typedef struct	signal
{
	char	*name;
	char	*type;
}	t_signal;

typedef struct	blueprint
{
	char	*text[2];
	t_parr	types;
	t_parr	qualities;
	t_parr	signals;
}	t_blueprint;

/* ----- PROTOTYPES ----- */

// signals/
//	load.c
bool	load_blueprint(t_data *data);
//	check.c
bool	check_blueprint_syntax(const cJSON *blueprint);
//	get.c
bool	init_blueprint(t_blueprint *blueprint, const cJSON *json_blueprint);
//	utils.c
char	*get_type(t_parr *types, char *type);
ssize_t	get_i_type(t_parr *types, char *type);
//	free.c
void	free_blueprint(t_blueprint *blueprint);
