#pragma once

/* ----- MACROS ----- */

// Function macros
#define COLOR(color, string)	(color string DEFAULT)

// Color escape sequences
//	Default
#define DEFAULT	"\033[0m"
//	Colors
#define RED	"\033[31m"
#define YELLOW	"\033[33m"
