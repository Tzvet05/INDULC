#pragma once

/* ----- INCLUDES ----- */

#include <stdbool.h>
#include <unistd.h>

/* ----- MACROS ----- */

// Number bases prefixes
#define HEX_PREFIX	"0x"
#define OCT_PREFIX	"0o"
#define BIN_PREFIX	"0b"

// Number bases charsets
#define HEX_CHARSET	"0123456789abcdef"
#define DEC_CHARSET	"0123456789"
#define OCT_CHARSET	"01234567"
#define BIN_CHARSET	"01"

/* -----PROTOTYPES ----- */

bool	is_number(char* str);
bool	will_overflow(char* str, size_t n_bits);
ssize_t	get_number(char* str);
char*	get_charset(char* str);
