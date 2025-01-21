#include "malloc.h"

void	my_free(void *ptr)
{
	int	to_free_sz;

	if (ptr == NULL)
		return ;
	to_free_sz = update_alloc_lst(0, ptr, RM_ENTRY, NULL);
	if (to_free_sz == 0)
		write(2, "free: error: double free\n", 26);
	if (to_free_sz > MEDIUM_ENTRY)
		munmap(ptr, to_free_sz);
}
