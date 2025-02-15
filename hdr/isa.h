#pragma once

/* ----- INCLUDES ----- */

#include <stddef.h>
#include "parr.h"

/* ----- MACROS ----- */

// ISA Json file keys
//	ISA
#define JSON_ISA_KEY_NB_REGISTERS	"n_registers"
#define JSON_ISA_KEY_INSTRUCTIONS	"instructions"
#define JSON_ISA_KEY_FLAGS		"flags"
//		Instruction
#define JSON_ISA_KEY_INSTRUCTION_MNEMONICS	"mnemonics"
#define JSON_ISA_KEY_INSTRUCTION_OPCODE		"opcode"
#define JSON_ISA_KEY_INSTRUCTION_BITFIELDS	"bitfields"
//			Format
#define JSON_ISA_KEY_INSTRUCTION_BITFIELD_LEN	"len"
#define JSON_ISA_KEY_INSTRUCTION_BITFIELD_TYPE	"type"
//		Flag
#define JSON_ISA_KEY_FLAG_MNEMONICS		"mnemonics"
#define JSON_ISA_KEY_FLAG_CONDITION_CODE	"condition_code"

// Bitfield types strings
#define BITFIELD_TYPES	((const char* const[]){"opcode", "register", "immediate", "condition", "unused"})

// Number of different bitfield types
#define N_BITFIELD_TYPES	5

/* ----- ENUMERATIONS ----- */

// Bitfield type
typedef enum bitfield_type
{
	OPCODE = 0,
	REGISTER,
	IMMEDIATE,
	CONDITION,
	UNUSED
}	t_bitfield_type;

// Mnemonic type
typedef enum mnemonic_type
{
	INSTRUCTION = 0,
	FLAG
}	t_mnemonic_type;

/* ----- STRUCTURES ----- */

// Instruction format bitfield
typedef struct bitfield
{
	size_t		len;//	Length of the bitfield
	t_bitfield_type	type;//	Type of the bitfield
}	t_bitfield;

// Instruction format
typedef struct format
{
	size_t	n_opwords;//	Number of words in the instruction (operands + opcode)
	t_parr	bitfields;//	Array of bitfields
}	t_format;

// Instruction
typedef struct instruction
{
	size_t		opcode;//	Opcode of the instruction
	t_format	format;//	Format of the instruction
}	t_instruction;

// Mnemonic
typedef struct mnemonic
{
	t_parr		mnemonics;//		Array of all mnemonic strings
	void*		compilation_target;//	Pointer to the data to compile to
	t_mnemonic_type	type;//			Type of the data to compile to
}	t_mnemonic;

// ISA
typedef struct isa
{
	size_t	n_registers;//		Number of registers of the CPU
	t_parr	instructions;//		Array of all supported instructions
	t_parr	flags;//		Array of all supported flags
	t_parr	mnemonics;//		Array of all mnemonics and what they compile to
}	t_isa;
