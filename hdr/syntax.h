#pragma once

/* ----- INCLUDES ----- */

#include <stdbool.h>
#include <stdint.h>

/* ----- MACROS ----- */

// Function macros
#define SET_PARSING(parsing)	((parsing & MASK_PARSING) << POS_PARSING)
#define SET_BEHAVIOR(behavior)	((behavior & MASK_BEHAVIOR) << POS_BEHAVIOR)
#define GET_PARSING(info)	((info >> POS_PARSING) & MASK_PARSING)
#define GET_BEHAVIOR(info)	((info >> POS_BEHAVIOR) & MASK_BEHAVIOR)

// Bit masks
#define MASK_PARSING	1
#define MASK_BEHAVIOR	1

// Bit positions
#define POS_PARSING	0
#define POS_BEHAVIOR	1

// Syntax
//	Keywords
#define KEYWORD_COMMENT	";"
#define KEYWORD_DEFINE	"%define"
#define KEYWORD_LABEL	":"
//	Keywords list
#define KEYWORDS	\
{\
	.len = 3, \
	.obj_size = sizeof(t_keyword), \
	.arr = (t_keyword [])\
	{\
		{\
			.str = KEYWORD_COMMENT, \
			.info = SET_PARSING(FUSED) | SET_BEHAVIOR(PARSE_STOP)\
		}, \
		{\
			.str = KEYWORD_DEFINE, \
			.info = SET_PARSING(SPACED) | SET_BEHAVIOR(NONE)\
		}, \
		{\
			.str = KEYWORD_LABEL, \
			.info = SET_PARSING(FUSED) | SET_BEHAVIOR(NONE)\
		}\
	}\
}
//	Characters ignored during tokenization
#define IGNORED_CHARS	"\t\n\v\f\r ,"

/* ----- ENUMERATIONS ----- */

// Parsing
enum
{
	SPACED,
	FUSED
};

// Behavior
enum
{
	NONE,
	PARSE_STOP
};

/* ----- TYPES DECLARATIONS ----- */

typedef struct	lst	t_lst;
typedef struct	data	t_data;

/* ----- STRUCTURES ----- */

// Keyword
typedef struct	keyword
{
	char	*str;
	uint8_t	info;
}	t_keyword;

/* ----- PROTOTYPES ----- */

// syntax/
//	analysis.c
bool	analyse_syntax(t_data *data);
//	define.c
bool	check_define_syntax(t_data *data, t_lst **tokens_ptr);
//	label.c
bool	check_label_syntax(t_lst **tokens_ptr);
//	instruction.c
bool	check_instruction_syntax(t_data *data, t_lst **tokens_ptr);
