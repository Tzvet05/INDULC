#pragma once

/* ----- INCLUDES ----- */

#include <stdbool.h>
#include <stdint.h>
#include "cJSON.h"
#include "file.h"
#include "lst.h"
#include "isa.h"

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
bool	argument_checking(int argc, char** argv);

// isa/
//	isa_loading.c
ssize_t	get_bitfield_type(char* str);
bool	isa_loading(t_data* data);
//	get_isa.c
bool	init_isa(t_isa* isa, const cJSON* json_isa);
//	check_isa_syntax.c
bool	check_isa_syntax(const cJSON* isa);

// file/
//	file.c
void	close_files(t_data* data);
void	init_filenames(t_data* data, char** file_names);

// tokenization/
//	tokenization.c
bool	tokenization(t_data* data);

// preprocessing/
//	preprocessing.c
bool	preprocessing(t_data* data);

// symbol_table/
//	symbol_table_building.c
bool	is_label(t_lst* tokens);
bool	symbol_table_building(t_data* data);

// syntax/
//	syntax_analysis.c
bool	syntax_analysis(t_data* data);

// machine_code/
//	machine_code_generation.c
bool	machine_code_generation(t_data* data);

// utils/
//	compilation.c
uint64_t	build_mask(size_t len);
void*		get_compilation_target(t_isa* isa, char* str, t_mnemonic_type type);
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
