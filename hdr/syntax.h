#pragma once

/* ----- INCLUDES ----- */

#include "data.h"

/* ----- MACROS ----- */

// Syntax
//	Statements syntax
#define DEFINE_KEYWORD	"%define"
#define LABEL_KEYWORD	":"
#define COMMENT_KEYWORD	";"
//	Characters ignored during tokenization
#define IGNORED_CHARS	"\t\n\v\f\r ,"

/* ----- PROTOTYPES ----- */

// syntax/
//	syntax_define.c
bool	check_define_syntax(t_isa* isa, t_lst **tokens_ptr);
//	syntax_label.c
bool	check_label_syntax(t_lst **tokens_ptr);
//	syntax_instruction.c
bool	check_instruction_syntax(t_data* data, t_lst **tokens_ptr);
