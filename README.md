# INDULC

**Indu**strious **L**anguage **C**ompiler

Compiler for INDUL (**Indu**strious **L**anguage), an ASM-like language designed to be executed on the Industrious CPUs, a series of RISC Factorio CPUs

## USAGE

First, go into the INDULC/ directory and compile the program using
```bash
make
```

Then, you can run the compiler using
`./indulc [program infile] ([compiled outfile]) ([isa infile])`

`[program infile]` is the input text file containing the program to compile. You must have reading permissions for it.

`[compiled outfile]` is the output text file to write the compiled program in. You must have writing permissions for it. This argument is optional and will be replaced by a default argument `a.out` if left empty.

`[isa infile]` is the input Json file containing the ISA used for compilation. You must have reading permissions for it. This argument is optional and will be replaced by a default argument `isa.json` if left empty.

### Makefile rules

`make` compiles the program.

`clean` removes the object files.

`fclean` removes the executable and the object files.

`re` removes the executable, the object files, and recompiles.

## SYNTAX

Whitespace characters and commas (`','`) are ignored by the tokenizer.
All numeric values can be specified in base 10, base 2 with prefix `0b` or base 16 with prefix `0x` or `0X`.

### Instructions

An instruction follows this syntax :

`[mnemonic] [operand 1] [...] [operand n]`

`[mnemonic]` is the mnemonic string of the instruction. It must be supported by the provided ISA.

`[operand]` is an operand of the instruction. It can be a register, an immediate, a macro, a label or a flag. Each instruction has a specific number and types of operands, specified in the provided ISA.

#### Registers

A register can be either a macro or a number that can start with the character `'r'` (case doesn't matter). Its index must be in range of the amount of registers specified by the provided ISA.

#### Immediates

An immediate can be either a number, a macro or a label.

#### Flags

A flag can be either a number or a mnemonic string. The mnemonic string must be supported by the provided ISA. Its value must be in range of the amount of flags supported by the provided ISA.

### Defines

A define statement follows this syntax :

`%define [identifier] [value]`

`[identifier]` is the identifier of the macro. It is the string that will be replaced by the value associated with it. It must start with an alphabetic character.

`[value]` is the value of the macro. It is the string that will replace the identifier associated with it.

A define statement must be on its own line.

If a redefinition occurs (a define statement specifies an already used identifier), the value associated to that identifier is replaced by the new value going forward (but the previously substituted identifiers are not updated retroactively).

### Labels

A label statement follows this syntax :

`[label]:`

`[label]` is the name of the label. It must start with an alphabetic character.

A label statement can either be on its own line (and will point to the address following itself) or before an instruction (and will point to its own address).

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

	ILD	r1,	START		; initialize r1
	ILD	r2,	STEP		; initialize r2
loop:	SUB	r1,	r2,	r1	; r1 = r1 - r2
	BRH	nz,	loop		; jump to loop label if result of substraction is not 0
	HLT				; stop program execution
```

## COMPILATION PROCESS

1. Tokenization
2. Preprocessing (%define and macro substitution)
3. Symbol Table (label: and address substitution)
4. Syntax Analysis (syntax compliance (errors & warnings))
5. Machine Code Generation (encoding & binary machine code)

## WIP FEATURES

- Custom ISA provided by a Json file
