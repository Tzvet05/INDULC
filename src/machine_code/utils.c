#include "lst.h"
#include "isa.h"
#include "is.h"

size_t	count_instructions(t_isa *isa, t_lst *tokens)
{
	size_t	n_instructions = 0;
	while (tokens != NULL)
	{
		if (has_instruction(isa, tokens->content) == 1)
			n_instructions++;
		tokens = tokens->next;
	}
	return (n_instructions);
}
