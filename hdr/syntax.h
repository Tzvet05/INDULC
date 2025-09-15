#pragma once

/* ----- INCLUDES ----- */

#include <stdbool.h>

/* ----- MACROS ----- */

// Syntax
//	Statements syntax
#define DEFINE_KEYWORD	"%define"
#define LABEL_KEYWORD	":"
#define COMMENT_KEYWORD	";"
//	Characters ignored during tokenization
#define IGNORED_CHARS	"\t\n\v\f\r ,"

/* ----- TYPES DECLARATIONS ----- */

typedef struct	lst	t_lst;
typedef struct	data	t_data;

/* ----- PROTOTYPES ----- */

// syntax/
//	syntax_analysis.c
bool	analyse_syntax(t_data* data);
//	syntax_define.c
bool	check_define_syntax(t_data* data, t_lst **tokens_ptr);
//	syntax_label.c
bool	check_label_syntax(t_lst **tokens_ptr);
//	syntax_instruction.c
bool	check_instruction_syntax(t_data* data, t_lst **tokens_ptr);
