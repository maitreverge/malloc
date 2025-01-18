#include "malloc.h"

void	my_free(void *ptr)
{
	int	to_free_sz;

	if (ptr == NULL)
	{
		perror("free");
		exit(EXIT_FAILURE);
	}
	to_free_sz = update_alloc_lst(0, ptr, RM_ENTRY, NULL);
	if (to_free_sz > MEDIUM_ENTRY)
		munmap(ptr, to_free_sz);
}
