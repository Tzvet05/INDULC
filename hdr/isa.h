#pragma once

/* ----- INCLUDES ----- */

#include <stddef.h>
#include "parr.h"

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

// Instruction bitfield
typedef struct bitfield
{
	size_t		len;//	length (in bits) of the bitfield
	t_bitfield_type	type;//	type of the bitfield
}	t_bitfield;

// Instruction
typedef struct instruction
{
	size_t	n_opwords;//	number of words in the instruction (operands + 1)
	t_parr	bitfields;//	array of bitfields inside this format
	size_t	opcode;//	opcode of the instruction
}	t_instruction;

// Flag
typedef struct flag
{
	size_t	condition_code;//	condition code used by that flag
}	t_flag;

// Mnemonic
typedef struct mnemonic
{
	char**		mnemonic;//		array of all valid mnemonic strings
	void*		compilation_target;//	pointer to the data to compile to
	t_mnemonic_type	type;//			type of the data to compile to
}	t_mnemonic;

// Whole ISA ROM
typedef struct isa
{
	size_t	n_registers;//	number of general-purpose registers of the CPU
	size_t	n_flags;//	number of flags supported by the CPU
	t_parr	instructions;//	array of all supported instructions
	t_parr	flags;//	array of all supported flags
	t_parr	mnemonics;//	array of all mnemonics and what they compile to
}	t_isa;
