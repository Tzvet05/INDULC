#pragma once

/* ----- INCLUDES ----- */

#include <unistd.h>
#include "parr.h"

/* ----- MACROS ----- */

// ISA Json file keys
//	ISA
#define JSON_INSTRUCTION_LENGTH	"instruction_length"
#define JSON_REGISTERS		"registers"
#define JSON_INSTRUCTIONS	"instructions"
#define JSON_FLAGS		"flags"
//		Instruction
#define JSON_INSTRUCTION_MNEMONICS	"mnemonics"
#define JSON_INSTRUCTION_BITFIELDS	"bitfields"
//			Bitfield
#define JSON_INSTRUCTION_BITFIELD_LEN		"len"
#define JSON_INSTRUCTION_BITFIELD_TYPE		"type"
#define JSON_INSTRUCTION_BITFIELD_VALUE		"value"
//		Flag
#define JSON_FLAG_MNEMONICS		"mnemonics"
#define JSON_FLAG_CONDITION_CODE	"condition_code"

// Extremum bitfield lengths
#define BITFIELD_LEN_MIN	1
#define BITFIELD_LEN_MAX	64

// Bitfield types
#define N_BITFIELD_TYPES	4
#define BITFIELD_TYPES		((const char* const[]){"register", "immediate", "condition", "constant"})

/* ----- ENUMERATIONS ----- */

// Bitfield type
typedef enum bitfield_type
{
	REGISTER = 0,
	IMMEDIATE,
	CONDITION,
	CONSTANT
}	t_bitfield_type;

// Mnemonic type
typedef enum mnemonic_type
{
	INSTRUCTION = 0,
	FLAG
}	t_mnemonic_type;

/* ----- STRUCTURES ----- */

// Instruction bitfield
typedef struct bitfield
{
	size_t		len;//		Length of the bitfield
	t_bitfield_type	type;//		Type of the bitfield
	ssize_t		value;//	Stored value (if type == constant)
}	t_bitfield;

// Instruction
typedef struct instruction
{
	size_t	n_opwords;//	Number of words in the instruction (opcode + operands)
	t_parr	bitfields;//	Array of bitfields
}	t_instruction;

// Mnemonic
typedef struct mnemonic
{
	t_parr		mnemonics;//		Array of mnemonic strings
	void*		compilation_target;//	Pointer to the data to compile to
	t_mnemonic_type	type;//			Type of the data to compile to
}	t_mnemonic;

// ISA
typedef struct isa
{
	size_t	instruction_length;//	Length of the instructions (in bits)
	t_parr	registers;//		Array of register indexes
	t_parr	instructions;//		Array of supported instructions
	t_parr	flags;//		Array of supported flags
	t_parr	mnemonics;//		Array of mnemonics and what they compile to
}	t_isa;
