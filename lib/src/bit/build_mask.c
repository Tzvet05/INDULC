#include <stdint.h>
#include <stddef.h>

uint64_t	build_mask(size_t len)
{
	uint64_t	mask = len > 0;
	return ((((mask << (len - mask)) - 1) << 1) | 1);
}

