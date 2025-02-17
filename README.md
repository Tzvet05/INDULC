# INDULC

**Indu**strious **L**anguage **C**ompiler

Compiler for INDUL (**Indu**strious **L**anguage), an ASM-like language designed to be executed on the Industrious CPUs, a series of RISC Factorio CPUs.

## SETUP

Clone and go into the repository using
```sh
git clone --recursive-submodules git@github.com:Tzvet05/INDULC.git && cd INDULC/
```

Compile the program using
```sh
make
```

## USAGE

Run the compiler using
`./indulc [program infile] ([compiled outfile]) ([isa infile])`

`[program infile]` is the input text file containing the program to compile. You must have reading permissions for it.

`[compiled outfile]` is the output text file to write the compiled program in. You must have writing permissions for it. This argument is optional and will be replaced by a default argument `a.out` if left empty.

`[isa infile]` is the input Json file containing the ISA used for compilation. You must have reading permissions for it. This argument is optional and will be replaced by a default argument `isa.json` if left empty.

### Makefile rules

`make (all)` compiles the libraries and the program.

`make fclean` removes everything that got compiled.

`make clean` removes everything that got compiled except the executable and its dynamic library.

`make cleanindulc` removes the program's object files.

`make re` removes everything that got compiled and recompiles the libraries and the program.

`make reindulc` removes the program's object files and recompiles the program.

## INDUL SYNTAX

Whitespace characters and commas (`,`) are ignored by the tokenizer.
All numeric values can be specified in base 10, base 2 using the prefix `0b` or base 16 using the prefixe `0x`.

### Instructions

An instruction follows this syntax :

`[mnemonic] [operand 1] [...] [operand n]`

`[mnemonic]` is the mnemonic string of the instruction. It must be supported by the provided ISA.

`[operand]` is an operand of the instruction. It can be a register, an immediate, a flag, a macro or a label. Each instruction has a specific number and types of operands, specified by the provided ISA.

#### Registers

A register can be either a macro or a number that can start with the character `r` or `R`. Its index must be in range of the amount of registers specified by the provided ISA, starting at `r0`.

#### Immediates

An immediate can be either a number, a macro or a label.

#### Flags

A flag can be either a number or a mnemonic string. Its mnemonic string or value must be supported by the provided ISA.

### Defines

A define statement follows this syntax :

`%define [identifier] [value]`

`[identifier]` is the identifier of the macro. It is the string that will be replaced by the value associated with it. It must start with an alphabetic character.

`[value]` is the value of the macro. It is the string that will replace the identifier associated with it.

A define statement must be on its own line.

If a redefinition occurs (a define statement specifies an already used identifier), the value associated to that identifier is replaced by the new value moving forward (but the previously substituted identifiers are not replaced retroactively).

### Labels

A label statement follows this syntax :

`[label]:`

`[label]` is the name of the label. It must start with an alphabetic character.

A label statement can either be on its own line (and will compile to the address following itself) or on the same line as an instruction, before the instruction's mnemonic (and will compile to its own address).

Duplicate labels cannot exist.

### Comments

A comment follows this syntax :

`;[comment]`

`[comment]` is a string.

### Example

This is an example of a valid block of INDUL code :

```
%define START	10			; starting value
%define STEP	2			; step value

	ILD	r1,	START		; initialize r1 with START
	ILD	r2,	STEP		; initialize r2 with STEP
loop:	SUB	r1,	r2,	r1	; definition of label "loop", r1 = r1 - r2
	BRH	nz,	loop		; jump to label "loop" if the result of the substraction is not 0
	HLT				; stop program execution
```

## JSON ISA SYNTAX

The Json file providing the ISA must follow a strict syntax.
Whitespace characters are ignored during parsing.

### The main object

The main object must contain 3 items :
- `"n_registers"`, whose value (number) is the number of registers of the CPU.
- `"instructions"`, whose value (array of instruction objects) is the array of all the supported instructions.
- `"flags"`, whose value (array of flag objects) is the array of all the supported flags.

#### The instruction object

The instruction object must contain 3 items :
- `"mnemonics"`, whose value (array of strings) is the array of all of the instruction's mnemonics.
- `"opcode"`, whose value (number) is the opcode of the instruction.
- `"bitfields"`, whose value (array of bitfield objects) is the array of all of the instruction's bitfields.

##### The bitfield object

The bitfield object must contain 2 items :
- `"len"`, whose value (number) is the length (in bits) of the bitfield.
- `"type"`, whose value (string) is the type of the bitfield. The type can be `"opcode"`, `"register"`, `"immediate"`, `"condition"` or `"unused"`.

As the instructions are encoded on 32 bits, the sum of the lengths of an instruction's bitfields must not exceed 32. If it is inferior to 32 bits, all the remaining bits up to the 32nd are considered unused.
The `"unused"` type is used to add padding inside an instruction.

#### The flag object

The flag object must contain 2 items :
- `"mnemonics"`, whose value (array of strings) is the array of all of the flag's mnemonics.
- `"condition_code"`, whose value (number) is the code of the flag.

### Example

The instruction `JMP 5` with only mnemonic `JMP` and opcode `18` can be made of 3 bitfields:
- one opcode of 8 bits (mnemonic `JMP`).
- one unused field of 8 bits (padding).
- one immediate of 16 bits (immediate `5`).

It can therefore be stored as :
```json
{
	"mnemonics":
	[
		"JMP"
	],
	"opcode": 18,
	"bitfields":
	[
		{
			"len": 8,
			"type": "opcode"
		},
		{
			"len": 8,
			"type": "unused"
		},
		{
			"len": 16,
			"type": "immediate"
		}
	]
}
```

The flag `even` with multiple mnemonics `even` and `ev` and code `2` can be stored as :
```json
{
	"mnemonics":
	[
		"ev",
		"even"
	],
	"condition_code": 2
}
```

Refer to the `isa.json` file located at the root of the repository for an example of a full ISA.

## COMPILATION PROCESS

1. Tokenization
2. Preprocessing (macro saving & substitution)
3. Symbol table management (label saving)
4. Syntax analysis (syntax verification)
5. Machine code generation (label substitution & encoding)
