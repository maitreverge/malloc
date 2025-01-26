#include "malloc.h"

/*
	This certainly isn't optimized, but I think it works.
*/
void	*my_realloc(void *ptr, size_t size)
{
	char	*new = NULL;

	if (ptr == NULL)
		return (my_malloc(size));
	if (size == 0 && ptr != NULL)
		return (my_free(ptr), NULL);

	new = my_malloc(size);
	if (!new)
	{
		write(2, "boo!\n", 6);
		exit(EXIT_FAILURE);
	}
	ft_strlcpy(new, (char *)ptr, ft_strlen((char *)ptr));
	my_free(ptr);
	return ((void *)new);
}

// void	*my_realloc(void *ptr, size_t size)
// {
// 	t_show_alloc_mem	mem;
// 	char				*addr;

// 	if (ptr == NULL)
// 		return (my_malloc(size));
// 	if (size == 0 && ptr != NULL)
// 		return (my_free(ptr), 0);
	
// 	for (t_alloc_list *t = g_alloc_lst; t != NULL; t = t->next)
// 	{
// 		if (t->ptr == ptr)
// 		{
// 			mem = show_alloc_mem_set(NULL, NULL);
// 			if (ptr >= mem.small_ptr && ptr < SMALL_ALLOC)
// 				addr = find_new_small_chunk();
// 			else if (ptr >= mem.medium_ptr && ptr < MEDIUM_ALLOC)
// 				addr = find_new_medium_chunk();
// 			else
// 			{
// 				addr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
// 				for (size_t i = 0; i < t->alloc_size; i++)
// 					addr + i = ptr[i];
// 				munmap()
// 			}
// 		}
// 	}
// }
