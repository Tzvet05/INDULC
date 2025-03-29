#pragma once

/* ----- MACROS ----- */

// Executable name
#define EXECUTABLE_NAME	"indulc"

// Failing functions
#define FUNC_ACCESS	"access()"
#define FUNC_FOPEN	"fopen()"
#define FUNC_GETLINE	"getline()"
#define FUNC_MALLOC	"malloc()"
#define FUNC_FREAD	"fread()"
#define FUNC_FWRITE	"fwrite()"
#define FUNC_STAT	"stat()"
//	cJSON library
#define FUNC_CJSON_PARSE	"cJSON_Parse()"

// Error strings
//	Libraries
#define ERROR_CJSON_LIB	"cJSON library (libcjson.so)"
//		cJSON library
#define ERROR_CJSON_PARSE	"failed to parse content of Json file"
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
#define ERROR_FILE_STATUS	"failed to get file status"
//	ISA Syntax
#define ERROR_SYNTAX		"syntax error"
#define ERROR_TOKEN		"unrecognized token (token not supported by the provided ISA)"
#define ERROR_NOT_NUMBER	"number contains invalid characters (must be only base-related digits)"
#define ERROR_NEGATIVE_NUMBER	"number is strictly negative (must be >= 0)"
//		Define
#define ERROR_DEFINE			"define statement"
#define ERROR_DEFINE_TOO_FEW_ARGS	"incomplete statement (expected syntax : %define [word] [number])"
#define ERROR_DEFINE_TOO_MANY_ARGS	"statement has too many arguments (expected syntax : %define [word] [number])"
//		Label
#define ERROR_LABEL			"label statement"
#define ERROR_LABEL_TOO_FEW_ARGS	"incomplete statement, missing label name (expected syntax : [label]:)"
#define ERROR_LABEL_TOO_MANY_ARGS	"statement has too many arguments (expected syntax : [label]:)"
#define ERROR_LABEL_DUPLICATE		"duplicate label (duplicates cannot exist)"
//		Instruction
#define ERROR_INSTRUCTION		"instruction"
#define ERROR_INSTRUCTION_TOO_FEW_ARGS	"incomplete instruction, missing operand(s) (refer to the provided ISA)"
#define ERROR_INSTRUCTION_TOO_MANY_ARGS	"instruction has too many operands (refer to the provided ISA)"
//			Register
#define ERROR_INSTRUCTION_REGISTER		"register operand"
#define ERROR_INSTRUCTION_REGISTER_MNEMONIC	"unknown mnemonic (mnemonic not supported by the provided ISA)"
//			Immediate
#define ERROR_INSTRUCTION_IMMEDIATE	"immediate operand"
//			Condition
#define ERROR_INSTRUCTION_CONDITION		"condition operand"
#define ERROR_INSTRUCTION_CONDITION_MNEMONIC	"unknown mnemonic (mnemonic not supported by the provided ISA)"
//	Json syntax
#define ERROR_JSON_SYNTAX		"Json syntax error"
#define ERROR_JSON_MISSING_ITEM		"Json item missing"
#define ERROR_JSON_NOT_NUMBER		"Json item is not a number when it should be"
#define ERROR_JSON_NOT_STRING		"Json item is not a string when it should be"
#define ERROR_JSON_NOT_ARRAY		"Json item is not an array when it should be"
#define ERROR_JSON_NOT_OBJECT		"Json item is not an object when it should be"
#define ERROR_JSON_BITFIELD_TYPE	"unsupported bitfield type (must be one of the types specified in the README)"
#define ERROR_JSON_INVALID_NUMBER	"invalid numeric value"
#define ERROR_JSON_INSTRUCTION_TOO_LONG	"the sum of all the bitfields exceeds the maximum instruction length (must be <= to the maximum instruction length specified in the provided ISA)"

// Warning strings
//	Syntax
#define WARNING_SYNTAX		"syntax warning"
#define WARNING_OVERFLOW	"immediate does not fit in designated space and will overflow or underflow"
//		Define
#define WARNING_DEFINE			"define statement"
#define WARNING_DEFINE_USELESS		"useless macro (identifier should be different from its substitute)"
#define WARNING_DEFINE_FLAG		"conflicting identifier (identifier is identical to a flag's mnemonic provided by the ISA)"
#define WARNING_DEFINE_INSTRUCTION	"conflicting identifier (identifier is identical to an instruction's mnemonic provided by the ISA)"
#define WARNING_DEFINE_REGISTER		"conflicting identifier (identifier is identical to a register's mnemonic provided by the ISA)"
#define WARNING_DEFINE_NUMBER		"hazardous identifier (identifier is a number)"
#define WARNING_DEFINE_LABEL		"hazardous identifier (identifier is identical to the label declaration keyword)"
//		Instruction
#define WARNING_INSTRUCTION		"instruction"
#define WARNING_INSTRUCTION_REGISTER	"register operand"
#define WARNING_INSTRUCTION_IMMEDIATE	"immediate operand"
#define WARNING_INSTRUCTION_CONDITION	"condition operand"
#define WARNING_INSTRUCTION_LABEL	"label resolution"
//	Json syntax
#define WARNING_JSON_SYNTAX	"Json syntax warning"
