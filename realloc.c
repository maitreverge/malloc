#include "malloc.h"

void	*my_realloc(void *ptr, size_t size)
{
	t_show_alloc_mem	mem;

	if (ptr == NULL)
		return (my_malloc(size));
	if (size == 0 && ptr != NULL)
		return (my_free(ptr), 0);
	
	for (t_alloc_list *t = g_alloc_lst; t != NULL; t = t->next)
	{
		if (t->ptr == ptr)
		{
			mem = show_alloc_mem_set(NULL, NULL);
			if (ptr >= mem.small_ptr && ptr < SMALL_ALLOC)
				find_new_small_chunk();
			if (ptr >= mem.medium_ptr && ptr < MEDIUM_ALLOC)
				find_new_medium_chunk();
		}
	}
}
