#pragma once

/* ----- MACROS ----- */

// Failing functions
#define FUNC_ACCESS	"access()"
#define FUNC_FOPEN	"fopen()"
#define FUNC_GETLINE	"getline()"
#define FUNC_MALLOC	"malloc()"
#define FUNC_FWRITE	"fwrite()"

// Error strings
//	Argument
#define ERROR_TOO_FEW_ARGS	"too few arguments provided (expected arguments : ./indulc [program infile] ([program outfile]) ([isa infile]))"
#define ERROR_TOO_MANY_ARGS	"too many arguments provided (expected arguments : ./indulc [program infile] ([program outfile]) ([isa infile]))"
//	Allocation
#define ERROR_FAILED_ALLOC	"failed memory allocation"
//	File
#define ERROR_FILE_NONEXISTANT	"file does not exist"
#define ERROR_READ_PERM		"file permissions prohibit reading"
#define ERROR_WRITE_PERM	"file permissions prohibit writing"
#define ERROR_OPEN_FILE		"failed to open file"
#define ERROR_READ_FILE		"failed to read file"
#define ERROR_WRITE_FILE	"failed to write to file"
//	Syntax
#define ERROR_SYNTAX			"syntax error"
#define ERROR_UNRECOGNIZED_TOKEN	"unrecognized token (token not supported by the provided ISA)"
#define ERROR_NOT_NUMBER		"number contains non-digit characters"
#define ERROR_NEGATIVE_NUMBER		"number is negative (must be >= 0)"
//		Type
#define ERROR_DEFINE		"define statement"
//			Description
#define ERROR_DEFINE_TOO_FEW_ARGS	"incomplete statement (expected syntax: %define [word] [number])"
#define ERROR_DEFINE_TOO_MANY_ARGS	"statement has too many arguments (expected syntax: %define [word] [number])"
#define ERROR_DEFINE_INVALID_NAME	"invalid macro name (must not start by a digit)"
//		Type
#define ERROR_LABEL		"label statement"
//			Description
#define ERROR_LABEL_TOO_FEW_ARGS	"incomplete statement, missing label name (expected syntax: [label]:)"
#define ERROR_LABEL_TOO_MANY_ARGS	"statement has too many arguments (expected syntax: [label]:)"
#define ERROR_LABEL_INVALID_NAME	"invalid label name (must not start by a digit)"
#define ERROR_LABEL_DUPLICATE		"duplicate label"
//		Type
#define ERROR_INSTRUCTION	"instruction"
//			Description
#define ERROR_INSTRUCTION_TOO_FEW_ARGS	"incomplete instruction, missing operand(s) (refer to ISA)"
#define ERROR_INSTRUCTION_TOO_MANY_ARGS	"instruction has too many operands (refer to ISA)"
#define ERROR_INSTRUCTION_REGISTER	"register index is too high (refer to ISA)"
#define ERROR_INSTRUCTION_FLAG		"flag index is too high (refer to ISA)"

// Warning strings
//	Syntax
#define WARNING_SYNTAX		"syntax warning"
#define WARNING_OVERFLOW	"immediate does not fit in designated space and will overflow or underflow"
//		Type
#define WARNING_DEFINE		"define statement"
//		Type
#define WARNING_INSTRUCTION	"instruction"
