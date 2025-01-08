#include "malloc.h"

void	*my_realloc(void *ptr, size_t size)
{
	if (ptr == NULL)
	{
		perror("realloc");
		exit(EXIT_FAILURE);
	}
	return (my_malloc(size));
}
