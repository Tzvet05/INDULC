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
#define N_BITFIELD_TYPES	4
#define BITFIELD_TYPES		((const char* const[]){"register", "immediate", "flag", "constant"})

/* ----- TYPES DECLARATIONS ----- */

typedef struct	data	t_data;

/* ----- ENUMERATIONS ----- */

// Bitfield type
typedef enum bitfield_type
{
	REGISTER,
	IMMEDIATE,
	FLAG,
	CONSTANT
}	t_bitfield_type;

/* ----- STRUCTURES ----- */

// Instruction bitfield
typedef struct bitfield
{
	size_t		len;//		Length of the bitfield (in bits)
	t_bitfield_type	type;//		Type of the bitfield
	ssize_t		value;//	Stored value (if type == CONSTANT)
}	t_bitfield;

// Instruction
typedef struct instruction
{
	t_parr	mnemonics;//	Array of mnemonic strings
	size_t	n_opwords;//	Number of words in the instruction (opcode + operands)
	t_parr	bitfields;//	Array of bitfields
}	t_instruction;

// Flag
typedef struct flag
{
	t_parr	mnemonics;//	Array of mnemonic strings
	size_t	code;//		Flag code
}	t_flag;

// Register
typedef struct _register
{
	t_parr	mnemonics;//	Array of mnemonic strings
	size_t	index;//	Register index
}	t_register;

// ISA
typedef struct isa
{
	size_t	instruction_length;//	Length of the instructions (in bits)
	t_parr	registers;//		Array of supported registers
	t_parr	instructions;//		Array of supported instructions
	t_parr	flags;//		Array of supported flags
}	t_isa;

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
