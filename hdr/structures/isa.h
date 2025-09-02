#pragma once

/* ----- INCLUDES ----- */

#include <sys/types.h>
#include "parr.h"

/* ----- ENUMERATIONS ----- */

// Bitfield type
typedef enum bitfield_type
{
	REGISTER = 0,
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
