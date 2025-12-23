#include "lst.h"
#include "tokenization.h"
#include "preprocessing.h"
#include "error.h"

void	check_macros(lst_t *macro_table)
{
	lst_t	*macro = macro_table;
	while (macro != NULL)
	{
		if (((macro_t *)macro->content)->n_uses == 0)
			fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: \"%s\"\n",
				EXECUTABLE_NAME, WARNING_SYNTAX,
				((macro_t *)macro->content)->identifier->lin,
				((macro_t *)macro->content)->identifier->col, WARNING_DEFINE,
				WARNING_DEFINE_UNUSED,
				((macro_t *)macro->content)->identifier->str);
		macro = macro->next;
	}
}
