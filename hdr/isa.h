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

// Bitfield
typedef struct bitfield
{
	size_t		bit_len;
	t_bitfield_type	type;
}	t_bitfield;

// Instruction format
typedef struct format
{
	size_t	n_opwords;//		number of words in the instruction (operands + 1)
	t_parr*	bitfield_lengths;//	pointer to array of bitfield lengths (size_t)
	t_parr	bitfield_types;//	array of bitfield types (size_t)
}	t_format;

// Instruction
typedef struct instruction
{
	t_format*	format;//	pointer to the instruction's format
	size_t		opcode;//	opcode of the instruction
}	t_instruction;

// Mnemonic
typedef struct mnemonic
{
	char**		mnemonic;//		array of all valid mnemonic strings
	void*		compilation_target;//	pointer to the data to compile to
	t_mnemonic_type	type;//			type of the data to compile to
}	t_mnemonic;

// ISA ROM
typedef struct isa
{
	size_t	n_registers;//		number of general-purpose registers of the CPU
	size_t	n_flags;//		number of flags supported by the CPU
	t_parr	bitfield_lengths;//	array of bitfield lengths (size_t)
	t_parr	formats;//		array of instruction formats
	t_parr	instructions;//		array of all supported instructions
	t_parr	flags;//		array of all supported flags (size_t)
	t_parr	mnemonics;//		array of all mnemonics and what they compile to
}	t_isa;
