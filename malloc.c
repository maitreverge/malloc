#include "malloc.h"

int	update_alloc_lst(size_t size, void *ptr, bool method)
{
	t_alloc_list *new; 
	t_alloc_list *prev = NULL;
	t_alloc_list *temp = g_alloc_lst;

	if (method == ADD_ENTRY)
	{
		new = malloc(sizeof(t_alloc_list)); //not allowed to use malloc, but for testing purposes this is okay

		if (ft_lstsize((t_list *)&g_alloc_lst) == 0)
		{
			g_alloc_lst->alloc_size = size;
			g_alloc_lst->ptr = ptr;
			g_alloc_lst->next = NULL;
		}
		ft_lstadd_front((t_list **)&g_alloc_lst, (t_list *)new);
		printf("added entry of size %ld with address %p\n", size, ptr);//////////
		return (-1);
	}
	if (g_alloc_lst == NULL || ft_lstsize((t_list *)&g_alloc_lst) == 0)
	{
		write(2, "free: error: double free\n", 26);
		exit(EXIT_FAILURE);
	}
	while (temp != NULL)
	{
		if (ptr == temp->ptr)
		{
			//delete node here
			//this is really sloppy but ok for now
			if (prev != NULL)
				prev->next = temp->next;
			printf("removed entry of size %ld with address %p\n", temp->alloc_size, ptr);//////////
			return (temp->alloc_size);
		}
		prev = temp;
		temp = temp->next;
	}
	return (0);
}

void	my_free(void *ptr)
{
	printf("my free called\n");
	int	to_free_sz;

	if (ptr == NULL)
	{
		perror("free");
		exit(EXIT_FAILURE);
	}
	to_free_sz = update_alloc_lst(0, ptr, RM_ENTRY);
	munmap(ptr, to_free_sz);
}


void	*my_malloc(size_t size)
{
	printf("my malloc called\n");
	char *addr;

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
	char *s = my_malloc(42);

	for (int i = 0; i < 142; i++)
		s[i] = 'a';
	s[42] = '\0';
	
	// write(1, s, 42);

	my_free(s);
	return (0);
}