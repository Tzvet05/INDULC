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

// Number of blueprint texts
#define N_TEXTS	2

/* ----- ENUMERATIONS ----- */

enum
{
	LABEL,
	DESCRIPTION
};

/* ----- TYPES DECLARATIONS ----- */

typedef struct	data	data_t;
typedef struct	pstr	pstr_t;

/* ----- STRUCTURES ----- */

typedef struct	signal
{
	char	*name;
	char	*type;
}	signal_t;

typedef struct	blueprint
{
	char	*text[N_TEXTS];
	parr_t	types;
	parr_t	qualities;
	parr_t	signals;
}	blueprint_t;

/* ----- PROTOTYPES ----- */

// signals/
//	load.c
bool	load_blueprint(data_t *data);
//	check.c
bool	check_blueprint_syntax(const cJSON *blueprint);
//	get.c
bool	init_blueprint(blueprint_t *blueprint, pstr_t *input_name, const cJSON *json_blueprint);
//	utils.c
char	*get_type(parr_t *types, char *type);
ssize_t	get_i_type(parr_t *types, char *type);
//	free.c
void	free_blueprint(blueprint_t *blueprint);
