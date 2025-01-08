#include "malloc.h"

void	my_free(void *ptr)
{
	if (ptr == NULL)
	{
		perror("free");
		exit(EXIT_FAILURE);
	}
	munmap(ptr, 42);	//VERY SUPER TEMPORARY, FIX THIS
}

void	*my_malloc(size_t size)
{
	char *addr;

	addr = mmap(NULL, size, PROT_READ | PROT_WRITE, 
		MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (addr == MAP_FAILED)
	{
		perror("mmap");
		exit(EXIT_FAILURE);
	}
	return (addr);
}


int main(void)
{
	char *s = my_malloc(42);

	//why is it letting me do this?
	for (int i = 0; i < 142; i++)
		s[i] = 'a';
	s[42] = '\0';
	
	//why is it letting me do this?
	write(1, s, 420);

	my_free(s);
	return (0);
}