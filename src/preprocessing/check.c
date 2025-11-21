#include "lst.h"
#include "tokenization.h"
#include "preprocessing.h"
#include "error.h"

void	check_macros(t_lst *macro_table)
{
	t_lst	*macro = macro_table;
	while (macro != NULL)
	{
		if (((t_macro *)macro->content)->n_uses == 0)
			fprintf(stderr, "%s: %s (%zu:%zu): %s: %s: \"%s\"\n",
				EXECUTABLE_NAME, WARNING_SYNTAX,
				((t_macro *)macro->content)->identifier->lin,
				((t_macro *)macro->content)->identifier->col, WARNING_DEFINE,
				WARNING_DEFINE_UNUSED,
				((t_macro *)macro->content)->identifier->str);
		macro = macro->next;
	}
}
