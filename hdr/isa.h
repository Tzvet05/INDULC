#pragma once

/* ----- INCLUDES ----- */

#include <sys/types.h>
#include "cJSON.h"
#include "parr.h"

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
#define BITFIELD_TYPES		{"register", "immediate", "flag", "constant", NULL}

/* ----- ENUMERATIONS ----- */

// Bitfield type
typedef enum	bitfield_type
{
	REGISTER,
	IMMEDIATE,
	FLAG,
	CONSTANT
}	bitfield_type_t;

/* ----- TYPES DECLARATIONS ----- */

typedef struct	data	data_t;

/* ----- STRUCTURES ----- */

// Instruction bitfield
typedef struct	bitfield
{
	size_t		len;//		Length of the bitfield (in bits)
	bitfield_type_t	type;//		Type of the bitfield
	ssize_t		value;//	Stored value (if type == CONSTANT)
}	bitfield_t;

// Instruction
typedef struct	instruction
{
	parr_t	mnemonics;//	Array of mnemonic strings
	size_t	n_opwords;//	Number of words in the instruction (opcode + operands)
	parr_t	bitfields;//	Array of bitfields
}	instruction_t;

// Flag
typedef struct	flag
{
	parr_t	mnemonics;//	Array of mnemonic strings
	size_t	code;//		Flag code
}	flag_t;

// Register
typedef struct	_register
{
	parr_t	mnemonics;//	Array of mnemonic strings
	size_t	index;//	Register index
}	_register_t;

// ISA
typedef struct	isa
{
	size_t	instruction_length;//	Length of the instructions (in bits)
	parr_t	registers;//		Array of supported registers
	parr_t	instructions;//		Array of supported instructions
	parr_t	flags;//		Array of supported flags
}	isa_t;

/* ----- PROTOTYPES ----- */

// isa/
//	load.c
bool	load_isa(data_t *data);
//	check.c
bool	check_isa_syntax(const cJSON *isa);
//	get.c
bool	init_isa(isa_t *isa, const cJSON *json_isa);
//	utils.c
ssize_t	get_bitfield_type(char *str);
//	free.c
void	free_isa(isa_t *isa);
