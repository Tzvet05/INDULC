#pragma once

/* ----- INCLUDES ----- */

#include <stdbool.h>
#include <sys/types.h>

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

// nbr/
//	is_number.c
bool	is_number(char *str);
//	will_overflow_str.c
bool	will_overflow_str(char *str, size_t n_bits);
//	will_overflow_int.c
bool	will_overflow_int(ssize_t nbr, size_t n_bits);
//	get_number.c
ssize_t	get_number(char *str);
//	get_charset.c
char	*get_charset(char *str);
