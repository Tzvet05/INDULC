# INDULC

**Indu**strious **L**anguage **C**ompiler

Assembler for INDUL (**Indu**strious **L**anguage), an ASM-like language originally designed to be executed on the Industrious CPUs, a series of RISC Factorio CPUs.

INDULC can directly generate Factorio blueprint strings to import in-game, but it can also only generate the assembled machine code, making it useful for many other uses.

## SETUP

Clone and go into the repository using
```sh
git clone --recurse-submodules git@github.com:Tzvet05/INDULC.git && cd INDULC/
```

Compile the program using
```sh
make
```

### Makefile rules

`make (all)` compiles the libraries and the program.

`make fclean` removes everything that got compiled.

`make clean` removes everything that got compiled except the executable and its dynamic library.

`make cleanindulc` removes the program's object files.

`make re` removes everything that got compiled and recompiles the libraries and the program.

`make reindulc` removes the program's object files and recompiles the program.

## USAGE

Run the assembler using
`./indulc {input}`

`{input}` is the mandatory input text file containing the program to assemble.
INDULC must have reading permissions for it.

The default output file in which the assembled machine code is written is named `a.out`. This name can be changed using the "output file" option (see further down). If it does not exist, INDULC will create it. If it already exists, INDULC must have writing permissions for it.

The default input file from which the ISA is read is named `isa.json`. This name can be changed using the "ISA file" option (see further down). INDULC must have reading permissions for it.

The default input file from which the signals are read is named `signals.json`. This name can be changed using the "signals file" option (see further down). INDULC must have reading permissions for it.

### Options

Options can be added anywhere in the arguments when running the assembler, except among an option's arguments.

They may support multiple names, they may require a parameter, and they may require arguments. The default parameters and arguments are indicated by `[ ]`. If the option requires arguments, they are indicated by `{ }`, and no options can be specified until all the arguments are provided.

If the same option is specified multiple times, the last occurence prevails.

The `--` argument can be used to indicate the end of option parsing. Any argument following it will be treated as a regular argument rather than as an option.

#### Help

`-h|--help`

The "help" option displays the usage help. It doesn't run the assembling process.

#### Version

`--version`

The "version" option displays INDULC's version. It doesn't run the assembling process.

#### Macro warnings

`-mw|--macro-warnings=no|[yes]`

When the "macro warnings" option is disabled, the syntax warnings for macros whose identifiers are identical to a flag mnemonic, to a register mnemonic, to a number, to the label definition keyword or to the macro definition keyword are muted.

#### ISA only

`-j|--isa-only=[no]|yes`

When the "ISA only" option is enabled, INDULC only checks the ISA's syntax, and doesn't check the INDUL code's syntax nor outputs a machine code file.

#### Syntax only

`-s|--syntax-only=[no]|yes`

When the "syntax only" option is enabled, INDULC only checks the INDUL code's syntax, and doesn't output a machine code file.

#### ISA file

`-i|--isa-file {file}|[isa.json]`

`{file}` is the name of the ISA file.

The "isa file" option can be used to specify the name of the input Json file from which the ISA is read. INDULC must have reading permissions for it.

#### Signals file

`-si|--signals-file {file}|[signals.json]`

`{file}` is the name of the signals file.

The "signals file" option can be used to specify the name of the input Json file from which the Factorio signals are read. INDULC must have reading permissions for it.

#### Machine code output

`-mo|--machine-code-output=[no]|bin|ascii`

The "machine code output" option can be used to specify how, if at all, the machine code is written. It can be in binary or using ASCII characters `0` and `1`. If a file is used and does not exist, INDULC will create it and name it `machine_code.bin` or `machine_code.txt` depending on the specified option. If it already exists, INDULC must have writing permissions for it.

#### Json output

`-jo|--json-output=[no]|compact|format`

The "json output" option can be used to specify how, if at all, the Json blueprint item is written. It can be compact or formatted with whitespaces. If a file is used and does not exist, INDULC will create it and name it `blueprint.json`. If it already exists, INDULC must have writing permissions for it.

#### String output

`-o|--string-output=no|terminal|file|[all]`

The "string output" option can be used to specify where, if at all, the blueprint string is written. It can be in the terminal, in a file or in both. If a file is used and does not exist, INDULC will create it and name it `string.txt`. If it already exists, INDULC must have writing permissions for it.

## INDUL SYNTAX

Whitespace characters and commas (`,`) are ignored by the tokenizer.
All numeric values can be specified in base 10, base 2 using the prefix `0b`, base 8 using the prefix `0o` or base 16 using the prefixe `0x`.

### Defines

A define statement follows this syntax :

`%define {identifier} {value}`

`{identifier}` is the identifier of the macro.
It is the string that will be replaced by the value associated with it.

`{value}` is the value of the macro.
It is the string that will replace the identifier associated with it.

A define statement must be on its own line.

If a redefinition occurs (a define statement specifies an already used identifier), the value associated to that identifier is replaced by the new value moving forward (but the previously substituted identifiers are not replaced retroactively).

### Labels

A label statement follows this syntax :

`{label}:`

`{label}` is the name of the label.

A label statement can either be on its own line (and will assemble to the address following itself) or on the same line as an instruction, before the instruction's mnemonic (and will assemble to its own address).

Duplicate labels cannot exist.

### Instructions

An instruction follows this syntax :

`{mnemonic} {operand 1} {...} {operand n}`

`{mnemonic}` is the mnemonic string of the instruction. It must be supported by the provided ISA.

`{operand}` is an operand of the instruction. It can be a register, an immediate, a flag, a macro or a label.
Each instruction has a specific number and types of operands, specified by the provided ISA.

An instruction must be on its own line.

#### Registers

A register can be either a macro or a mnemonic string.

#### Immediates

An immediate can be either a number, a macro or a label.

#### Flags

A flag can be either a macro or a mnemonic string.

### Comments

A comment follows this syntax :

`;{comment}`

`{comment}` is a string.

A comment can be started anywhere.

### Example

Here is an example of a valid block of INDUL code :
```
%define START	10					; starting value
%define STEP	2					; step value

		ILOD	r1,		START		; initialize r1 with START
		ILOD	r2,		STEP		; initialize r2 with STEP
loop:	SUB		r1,		r2,		r1	; definition of label "loop", r1 = r1 - r2
		BRH		nz,		loop		; jump to the label "loop" if the result of the substraction is not 0
		HLT							; stop program execution
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

The instruction `JMPI 5` with only mnemonic `JMPI` and opcode `30` can be made of 3 bitfields:
- one constant of 8 bits (holding the opcode (`30` here)).
- one constant of 8 bits (padding).
- one immediate of 16 bits (holding the target address (`5` here)).

It can therefore be stored as :
```json
{
	"mnemonics":
	[
		"JMPI"
	],
	"bitfields":
	[
		{
			"len": 8,
			"type": "constant",
			"value" : 30
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

## JSON SIGNALS SYNTAX

The Json file providing the Factorio signals must follow a strict syntax.
Whitespace characters are ignored during parsing.

### The main object

The main object must contain 1 to 3 items :
- `"types"`, whose value (array of strings) is the array of all internal signal types.
- `"qualities"`, whose value (array of strings) is the array of all signal qualities.
- `"signals"`, whose value (array of signal objects) is the array of all signals.

`"types"` can be absent or empty if no signal specifies a type.

`"qualities"` can be absent or empty.

The generated blueprint lists instructions in the same order as signal types are listed. Typeless signals are implicitely listed first.

The generated blueprint will use all the specified qualities to store instructions. If no qualities are specified, the blueprint will be devoid of quality-related fields.

#### The signal object

The signal object must contain 1 to 2 items :
- `"type"`, whose value (string) is the internal type of the signal.
- `"name"`, whose value (string) is the name of the signal.

`"type"` can be absent.
The type specified by the signal must be listed in the `"types"` item of the main object at the desired index.

The generated blueprint lists instructions in the same order as signals are listed relative to their type category.

### Example

A valid signals file can look like this :
```json
{
	"types":
	[
		"fluid",
		"virtual"
	],
	"qualities":
	[
		"normal",
		"uncommon"
	],
	"signals":
	[
		{
			"type": "virtual",
			"name": "shape-vertical"
		},
		{
			"name": "wooden-chest"
		},
		{
			"type": "fluid",
			"name": "steam"
		},
		{
			"name": "iron-chest"
		}
	]
}
```

The instructions would be stored as signals in the following order :
1. `"wooden-chest"`, `"normal"` (typeless instructions come first, the first listed signal in the typeless category is `"wooden-chest"`, the first listed quality is `"normal"`)
2. `"wooden-chest"`, `"uncommon"` (the second listed quality is `"uncommon"`)
3. `"iron-chest"`, `"normal"` (the second listed signal in the typeless category is `"iron-chest"`)
4. `"iron-chest"`, `"uncommon"`
5. `"steam"` (`"fluid"`), `"normal"` (the first listed type is `"fluid"`)
6. `"steam"` (`"fluid"`), `"uncommon"`
7. `"shape-vertical"` (`"virtual"`), `"normal"` (the third listed type is `"virtual"`)
8. `"shape-vertical"` (`"virtual"`), `"uncommon"`

Refer to the `signals.json` file located at the root of the repository for an example of a complete Factorio signals file.

## ASSEMBLY PROCESS

1. Tokenization
2. Preprocessing (macro saving & substitution)
3. Symbol table building (label saving)
4. Syntax analysis (syntax verification)
5. Machine code generation (label substitution & encoding)

6. Factorio Json blueprint item building
7. Factorio blueprint string convertion

## CREDITS

A special thanks to the contributors of :
- [cJSON](https://github.com/DaveGamble/cJSON) - Used for the parsing and building of Json objects
