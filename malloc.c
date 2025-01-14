#include "malloc.h"

t_alloc_list	*g_alloc_lst = NULL;

char	*alloc_from_small_zone()
{
	return (NULL);
}

char	*alloc_from_medium_zone()
{
	return (NULL);
}


/*
*	Preallocates the small and medium zones as specified in the subject,
*	and creates the allocation list.
*/
void	prealloc_zones(void)
{
	char		 	*small = NULL;
	char 			*medium = NULL;
	t_alloc_list	*prev = NULL;

	small = mmap(NULL, SMALL_ALLOC, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	medium = mmap(NULL, MEDIUM_ALLOC, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

	if (small == MAP_FAILED || medium == MAP_FAILED)
	{
		perror("mmap");
		exit(EXIT_FAILURE);
	}
	g_alloc_lst = (t_alloc_list *)(small + SMALL_ALLOC - (SMALL_ALLOC / 100 * 90));
	for (size_t i = (size_t)g_alloc_lst; (char *)(i + 24) < small + SMALL_ALLOC; i += 24)
	{
		g_alloc_lst->alloc_size = 0;
		g_alloc_lst->ptr = NULL;
		g_alloc_lst->next = (t_alloc_list *)(i + 24);
		prev = g_alloc_lst;
		g_alloc_lst = g_alloc_lst->next;
	}
	prev->next = (t_alloc_list *)(medium + MEDIUM_ALLOC - (MEDIUM_ALLOC / 100 * 95));
	g_alloc_lst = prev->next;
	for (size_t i = (size_t)g_alloc_lst; (char *)(i + 24) < medium + MEDIUM_ALLOC; i += 24)
	{
		g_alloc_lst->alloc_size = 0;
		g_alloc_lst->ptr = NULL;
		g_alloc_lst->next = (t_alloc_list *)(i + 24);
		prev = g_alloc_lst;
		g_alloc_lst = g_alloc_lst->next;
	}
	prev->next = NULL;
	g_alloc_lst = (t_alloc_list *)(small + SMALL_ALLOC - (SMALL_ALLOC / 100 * 90));
}

void	*my_malloc(size_t size)
{
	char				*addr;
	static u_int64_t	g_alloc_lst_size = 0;

	if (g_alloc_lst == NULL || g_alloc_lst_size == 0)
		prealloc_zones();
	if (size <= MEDIUM_ENTRY)
	{
		if (size <= SMALL_ENTRY)
			addr = alloc_from_small_zone();
		else
			addr = alloc_from_medium_zone();
	}
	else
	{
		addr = mmap(NULL, size, PROT_READ | PROT_WRITE, 
			MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
		if (addr == MAP_FAILED)
		{
			perror("mmap");
			exit(EXIT_FAILURE);
		}
	}
	update_alloc_lst(size, addr, ADD_ENTRY, &g_alloc_lst_size);
	return (addr);
}


int main(void)
{
	// printf("%ld\n", sizeof(u_int64_t));
	// return (0);
	char *a = my_malloc(42);
	char *b = my_malloc(13);
	char *c = my_malloc(222);

	my_free(a);
	my_free(b);
	my_free(c);
	return (0);
}