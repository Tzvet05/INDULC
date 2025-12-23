#pragma once

/* ----- INCLUDES ----- */

#include <stdbool.h>

/* ----- MACROS ----- */

// Json blueprint key fields
#define JSON_BLUEPRINT		"blueprint"
#define JSON_DESCRIPTION	"description"
#define JSON_ICONS		"icons"
#define JSON_SIGNAL		"signal"
#define JSON_NAME		"name"
#define JSON_INDEX		"index"
#define JSON_ENTITIES		"entities"
#define JSON_ENTITY_NUMBER	"entity_number"
#define JSON_POSITION		"position"
#define JSON_X			"x"
#define JSON_Y			"y"
#define JSON_DIRECTION		"direction"
#define JSON_CONTROL_BEHAVIOR	"control_behavior"
#define JSON_SECTIONS		"sections"
#define JSON_FILTERS		"filters"
#define JSON_TYPE		"type"
#define JSON_QUALITY		"quality"
#define JSON_COMPARATOR		"comparator"
#define JSON_COUNT		"count"
#define JSON_ITEM		"item"
#define JSON_LABEL		"label"
#define JSON_VERSION		"version"

// Json blueprint value fields
//	Blueprint
#define JSON_BLUEPRINT_DESCRIPTION	"Blueprint of an assembled INDUL program, stored in an array of constant combinators. Ready to be pasted onto the instruction ROM of a CPU."
#define JSON_BLUEPRINT_VERSION		562949958139904
//	Items
#define JSON_ITEM_BLUEPRINT		"blueprint"
#define JSON_ITEM_CONSTANT_COMBINATOR	"constant-combinator"
//	Entity attributes
#define JSON_ENTITY_DIRECTION		4
#define JSON_ENTITY_SECTION_INDEX	0
#define JSON_ENTITY_FILTER_COMPARATOR	"="

/* ----- TYPES DECLARATIONS ----- */

typedef struct	data	data_t;

/* ----- PROTOTYPES ----- */

// blueprint/
//	build_json.c
bool	build_json_blueprint(data_t *data);
//	build_string.c
bool	build_string_blueprint(data_t *data);
