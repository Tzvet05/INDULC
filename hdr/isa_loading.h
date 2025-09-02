#pragma once

/* ----- INCLUDES ----- */

#include "cJSON.h"
#include "isa.h"
#include "data.h"

/* ----- MACROS ----- */

// ISA Json file keys
//	ISA
#define JSON_INSTRUCTION_LENGTH	"instruction_length"
#define JSON_REGISTERS		"registers"
#define JSON_INSTRUCTIONS	"instructions"
#define JSON_FLAGS		"flags"
//		Register
#define JSON_REGISTER_MNEMONICS	"mnemonics"
#define JSON_REGISTER_INDEX	"index"
//		Instruction
#define JSON_INSTRUCTION_MNEMONICS	"mnemonics"
#define JSON_INSTRUCTION_BITFIELDS	"bitfields"
//			Bitfield
#define JSON_INSTRUCTION_BITFIELD_LEN		"len"
#define JSON_INSTRUCTION_BITFIELD_TYPE		"type"
#define JSON_INSTRUCTION_BITFIELD_VALUE		"value"
//		Flag
#define JSON_FLAG_MNEMONICS	"mnemonics"
#define JSON_FLAG_CODE		"code"

// Extremum bitfield lengths
#define BITFIELD_LEN_MIN	1
#define BITFIELD_LEN_MAX	64

// Bitfield types
#define N_BITFIELD_TYPES	4
#define BITFIELD_TYPES		((const char* const[]){"register", "immediate", "flag", "constant"})

/* ----- PROTOTYPES ----- */

// isa/
//	isa_loading.c
bool	load_isa(t_data* data);
//	check_isa_syntax.c
bool	check_isa_syntax(const cJSON* isa);
//	get_isa.c
bool	init_isa(t_isa* isa, const cJSON* json_isa);
//	isa_utils.c
ssize_t	get_bitfield_type(char* str);
//	free_isa.c
void	free_isa(t_isa* isa);
