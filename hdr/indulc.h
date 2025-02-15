#pragma once

/* ----- INCLUDES ----- */

#include <stdbool.h>
#include <stdint.h>
#include "file.h"
#include "lst.h"
#include "isa.h"

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

// Number bases prefixes
#define HEXA_PREFIX_UPPER	"0X"
#define HEXA_PREFIX_LOWER	"0x"
#define BIN_PREFIX		"0b"

// Number bases charsets
#define HEXA_CHARSET	"0123456789abcdef"
#define DEC_CHARSET	"0123456789"
#define BIN_CHARSET	"01"

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
bool	isa_loading(t_data* data);

// file/
//	file_opening.c
bool	open_file(t_file* file, char* mode);
//	init_filenames.c
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
t_bitfield*	get_bitfield(t_instruction* instr, size_t i_operand);
void*		get_compilation_target(t_isa* isa, char* str, t_mnemonic_type type);
//	nbr.c
bool	is_number(char* str);
bool	will_overflow(char* str, size_t n_bits);
ssize_t	get_number(char* str);
//	cmp.c
bool	cmp_label(void* label, void* str);
bool	cmp_macro(void* macro, void* str);
bool	cmp_token(void* token, void* str);
bool	cmp_flag(void* flag, void* ptr);

// free/
//	free_data.c
void	free_isa(t_isa* isa);
void	close_files(t_data* data);
void	free_label(void* label);
void	free_macro(void* macro);
void	free_tokens(t_lst* token_col);
