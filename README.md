# INDULC

**Indu**strious **L**anguage **C**ompiler

Assembler for INDUL (**Indu**strious **L**anguage), an ASM-like language designed to be executed on the Industrious CPUs, a series of RISC Factorio CPUs.

## SETUP

Clone and go into the repository using
```sh
git clone --recursive-submodules git@github.com:Tzvet05/INDULC.git && cd INDULC/
```

Compile the program using
```sh
make
```

### Mute macro warnings mode

When the mute macro warnings mode is enabled, the assembler runs less extensive syntax checks on macro definitions.

Changes :
- The syntax analysis does not perform syntax checks for macros whose identifier is identical to their substitute, to a flag mnemonic, to a register mnemonic, to a number, to the label definition keyword or to the macro definition keyword.

To enable the mute macro warnings mode, the environment variable `COMP_MUTE_MACRO_WARNINGS` must be set to `1` before compiling the assembler.

You can do so by executing the following command :
```sh
export COMP_MUTE_MACRO_WARNINGS=1
```

### Characters output mode

When the characters output mode is enabled, the assembler outputs the assembled program in a human-readable form.

Changes :
- The assembled program is written in the outfile using characters (`0` and `1`) rather than actual bits.

To enable the characters output mode, the environment variable `COMP_OUTPUT_CHARS` must be set to `1` before compiling the assembler.

You can do so by executing the following command :
```sh
export COMP_OUTPUT_CHARS=1
```

## USAGE

Run the assembler using
`./indulc [program infile] ([assembled outfile]) ([isa infile])`

`[program infile]` is the input text file containing the program to assemble.
You must have reading permissions for it.

`[assembled outfile]` is the output text file to write the assembled program in.
You must have writing permissions for it.
This argument is optional and will be replaced by a default argument `a.out` if left empty.

`[isa infile]` is the input Json file containing the ISA used for assembly.
You must have reading permissions for it.
This argument is optional and will be replaced by a default argument `isa.json` if left empty.

### Makefile rules

`make (all)` compiles the libraries and the program.

`make fclean` removes everything that got compiled.

`make clean` removes everything that got compiled except the executable and its dynamic library.

`make cleanindulc` removes the program's object files.

`make re` removes everything that got compiled and recompiles the libraries and the program.

`make reindulc` removes the program's object files and recompiles the program.

## INDUL SYNTAX

Whitespace characters and commas (`,`) are ignored by the tokenizer.
All numeric values can be specified in base 10, base 2 using the prefix `0b`, base 8 using the prefix `0o` or base 16 using the prefixe `0x`.

### Instructions

An instruction follows this syntax :

`[mnemonic] [operand 1] [...] [operand n]`

`[mnemonic]` is the mnemonic string of the instruction. It must be supported by the provided ISA.

`[operand]` is an operand of the instruction. It can be a register, an immediate, a flag, a macro or a label.
Each instruction has a specific number and types of operands, specified by the provided ISA.

An instruction must be on its own line.

#### Registers

A register can be either a macro or a mnemonic string.

#### Immediates

An immediate can be either a number, a macro or a label.

#### Flags

A flag can be either a macro or a mnemonic string.

### Defines

A define statement follows this syntax :

`%define [identifier] [value]`

`[identifier]` is the identifier of the macro.
It is the string that will be replaced by the value associated with it.

`[value]` is the value of the macro.
It is the string that will replace the identifier associated with it.

A define statement must be on its own line.

If a redefinition occurs (a define statement specifies an already used identifier), the value associated to that identifier is replaced by the new value moving forward (but the previously substituted identifiers are not replaced retroactively).

### Labels

A label statement follows this syntax :

`[label]:`

`[label]` is the name of the label.

A label statement can either be on its own line (and will assemble to the address following itself) or on the same line as an instruction, before the instruction's mnemonic (and will assemble to its own address).

Duplicate labels cannot exist.

### Comments

A comment follows this syntax :

`;[comment]`

`[comment]` is a string.

A comment can be started anywhere.

### Example

Here is an example of a valid block of INDUL code :
```
%define START	10			; starting value
%define STEP	2			; step value

	ILOD	r1,	START		; initialize r1 with START
	ILOD	r2,	STEP		; initialize r2 with STEP
loop:	SUB	r1,	r2,	r1	; definition of label "loop", r1 = r1 - r2
	BRH	nz,	loop		; jump to the label "loop" if the result of the substraction is not 0
	HLT				; stop program execution
```

## JSON ISA SYNTAX

The Json file providing the ISA must follow a strict syntax.
Whitespace characters are ignored during parsing.

### The main object

The main object must contain 4 items :
- `"instruction_length"`, whose value (number) is the maximum length (in bits) of the instructions.
- `"registers"`, whose value (array of register objects) is the array of all the supported CPU registers.
- `"instructions"`, whose value (array of instruction objects) is the array of all the supported instructions.
- `"flags"`, whose value (array of flag objects) is the array of all the supported flags.

`"instruction_length"` must be strictly greater than 0.
It does not need to be a multiple of 8, and if it is not, all the bits up to the nearest multiple of 8 will be written as 0 in the machine code (for padding reasons).

#### The register object

The register object must contain 2 items :
- `"mnemonics"`, whose value (array of strings) is the array of all of the register's mnemonics.
- `"index"`, whose value (number) is the index of the register.

#### The instruction object

The instruction object must contain 2 items :
- `"mnemonics"`, whose value (array of strings) is the array of all of the instruction's mnemonics.
- `"bitfields"`, whose value (array of bitfield objects) is the array of all of the instruction's bitfields.

The sum of the lengths of an instruction's bitfields must not exceed the value specified by `"instruction_length"` from the main object. If the sum is inferior to this value, all the remaining bits up to the value of `"instruction_length"` are treated as if they were part of a `"constant"` bitfield with a `"value"` of 0.

##### The bitfield object

The bitfield object must contain 2 to 3 items :
- `"len"`, whose value (number) is the length (in bits) of the bitfield.
- `"type"`, whose value (string) is the type of the bitfield.
- `"value"`, whose value (number) is the value of the constant (if the bitfield's type is `"constant"`).

`"len"` must be strictly greater than 0. It does not need to be a multiple of 8.

`"type"` must be one of `"constant"`, `"register"`, `"immediate"` and `"flag"`.
`"constant"` can be used for the opcode, padding or a constant value needed by a pseudoinstruction.

`"value"` is ignored if the bitfield's type is not `"constant"`. If the bitfield's type is `"constant"` but the `"value"` item does not exists, its value is considered equal to 0.

#### The flag object

The flag object must contain 2 items :
- `"mnemonics"`, whose value (array of strings) is the array of all of the flag's mnemonics.
- `"code"`, whose value (number) is the code of the flag.

### Example

The instruction `JMP 5` with only mnemonic `JMP` and opcode `18` can be made of 3 bitfields:
- one constant of 8 bits (holding the opcode (`18` here)).
- one constant of 8 bits (padding).
- one immediate of 16 bits (holding the target address (`5` here)).

It can therefore be stored as :
```json
{
	"mnemonics":
	[
		"JMP"
	],
	"bitfields":
	[
		{
			"len": 8,
			"type": "constant",
			"value" : 18
		},
		{
			"len": 8,
			"type": "constant"
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
	"code": 2
}
```

Refer to the `isa.json` file located at the root of the repository for an example of a complete ISA.

## ASSEMBLY PROCESS

1. Tokenization
2. Preprocessing (macro saving & substitution)
3. Symbol table management (label saving)
4. Syntax analysis (syntax verification)
5. Machine code generation (label substitution & encoding)
