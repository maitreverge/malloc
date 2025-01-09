#include "malloc.h"

/*
*	Preallocates the small and medium zones as specified in the subject
*	(ALLOC_SIZE) - (ALLOC_SIZE / 100 * 85)
*	-----------------------
*	85% of prealloc'd space is for malloc itself
*	other 15% is for g_alloc_lst
*/
void	prealloc_zones(void)
{
	char 	*small;
	char 	*medium;

	small = mmap(NULL, SMALL_ALLOC, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	medium = mmap(NULL, MEDIUM_ALLOC, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

	if (small == MAP_FAILED || medium == MAP_FAILED)
	{
		perror("mmap");
		exit(EXIT_FAILURE);
	}
	g_alloc_lst = small + SMALL_ALLOC;
	for (int i = g_alloc_lst - (SMALL_ALLOC / 100 * 85); i < small + SMALL_ALLOC; i += sizeof(t_alloc_list))
	{
		g_alloc_lst->next = 
	}
}

void	*my_malloc(size_t size)
{
	char *addr;

	if (g_alloc_lst == NULL || ft_lstsize(g_alloc_lst) == 0)
		prealloc_zones();
	addr = mmap(NULL, size, PROT_READ | PROT_WRITE, 
		MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (addr == MAP_FAILED)
	{
		perror("mmap");
		exit(EXIT_FAILURE);
	}
	update_alloc_lst(size, addr, ADD_ENTRY);
	return (addr);
}


int main(void)
{
	char *a = my_malloc(42);
	char *b = my_malloc(13);
	char *c = my_malloc(222);

	my_free(a);
	my_free(b);
	my_free(c);
	return (0);
}