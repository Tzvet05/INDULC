#pragma once

/* ----- INCLUDES ----- */

#include <stdbool.h>
#include <stdint.h>
#include "cJSON.h"
#include "file.h"
#include "lst.h"
#include "isa.h"
#include "token.h"

/* ----- ENUMERATIONS ----- */

// Files
enum
{
	INFILE_PROGRAM = 0,
	OUTFILE_PROGRAM,
	INFILE_ISA
};

/* ----- STRUCTURES ----- */

// Generic data storage
typedef struct data
{
	t_file	files[3];
	t_lst*	tokens;
	t_lst*	macro_table;
	t_lst*	symbol_table;
	t_isa	isa;
}	t_data;

/* ----- MACROS ----- */

// Executable name
#define EXECUTABLE_NAME	"indulc"

// Default file names
#define DEFAULT_OUTFILE_PROGRAM	"a.out"
#define DEFAULT_INFILE_ISA	"isa.json"

// Syntax
#define DEFINE_KEYWORD	"%define"
#define LABEL_KEYWORD	":"
#define COMMENT_KEYWORD	";"

/* ----- PROTOTYPES ----- */

// arguments/
//	argument_checking.c
bool	check_arguments(int n_files);

// isa/
//	isa_loading.c
bool	load_isa(t_data* data);
//	check_isa_syntax.c
bool	check_isa_syntax(const cJSON* isa);
//	get_isa.c
bool	init_isa(t_isa* isa, const cJSON* json_isa);
//	isa_utils.c
ssize_t	get_bitfield_type(char* str);

// file/
//	file.c
void	close_files(t_data* data);
void	init_filenames(t_data* data, char** file_names);
bool	check_files(t_data* data);

// tokenization/
//	tokenization.c
bool	tokenize(t_data* data);

// preprocessing/
//	preprocessing.c
bool	preprocess(t_data* data);
//	preprocessing_utils.c
bool	is_define(t_lst* tokens);

// symbol_table/
//	symbol_table_building.c
bool	build_symbol_table(t_data* data);
//	symbol_table_utils.c
bool	is_label(t_lst* tokens);
bool	has_instruction(t_isa* isa, t_lst* tokens);

// syntax/
//	syntax_analysis.c
bool	analyse_syntax(t_data* data);
//	syntax_define.c
bool	check_define_syntax(t_lst **tokens_ptr);
//	syntax_label.c
bool	check_label_syntax(t_lst **tokens_ptr);
//	syntax_instruction.c
bool	check_instruction_syntax(t_data* data, t_lst **tokens_ptr);

// machine_code/
//	machine_code_generation.c
bool	generate_machine_code(t_data* data);
//	get_operand.c
ssize_t	get_register_operand(t_token* token);
ssize_t	get_immediate_operand(t_lst* symbol_table, t_token* token);
ssize_t	get_condition_operand(t_isa* isa, t_token* token);

// utils/
//	assembling.c
uint64_t	build_mask(size_t len);
void*		get_assembling_target(t_isa* isa, char* str, t_mnemonic_type type);
//	cmp.c
bool	cmp_label(void* label, void* str);
bool	cmp_macro(void* macro, void* str);
bool	cmp_token(void* token, void* str);
bool	cmp_flag(void* flag, void* ptr);
bool	cmp_register(void* _register, void* ptr);

// free/
//	free_data.c
void	free_isa(t_isa* isa);
void	free_tokens(t_lst* token_col);
//	free_struct.c
void	free_label(void* label);
void	free_macro(void* macro);
void	free_token(void* token);
