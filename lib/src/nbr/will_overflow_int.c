#include <sys/types.h>
#include <stdbool.h>
#include "bit.h"

bool	will_overflow_int(ssize_t nbr, size_t n_bits)
{
	ssize_t	extremum = (ssize_t)build_mask(n_bits - (n_bits > 0));
	return (nbr > extremum || nbr < ~extremum);
}
