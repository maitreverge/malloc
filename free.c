#include "malloc.h"

//terribly bad for now
void	my_free(void *ptr)
{
	if (ptr == NULL)
	{
		perror("free");
		exit(EXIT_FAILURE);
	}
	munmap(ptr, 42);	//VERY SUPER TEMPORARY, FIX THIS
}
