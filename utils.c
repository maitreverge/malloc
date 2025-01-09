#include "malloc.h"

/*
*	Yes, there's an overhead to the subfunctions, 
*	but it looks way better than crunching them both into update_alloc_lst()
*/

static void update_alloc_lst_add(size_t size, void *ptr)
{
	t_alloc_list *new = NULL;
	t_alloc_list *temp;

	if (!(new = malloc(sizeof(t_alloc_list))))//not allowed to use malloc, but for testing purposes this is okay
		exit(EXIT_FAILURE);
	new->alloc_size = size;
	new->ptr = ptr;
	new->next = NULL;
	if (g_alloc_lst == NULL || ft_lstsize(&g_alloc_lst) == 0)
		g_alloc_lst = new;
	else
	{
		temp = (t_alloc_list *)ft_lstlast(g_alloc_lst);
		temp->next = new;
	}
	printf("added entry of size %ld with address %p\n", size, ptr);//////////
}

static int update_alloc_lst_rm(void *ptr)
{
	t_alloc_list *prev = NULL;
	t_alloc_list *temp = g_alloc_lst;

	if (g_alloc_lst == NULL || ft_lstsize(&g_alloc_lst) == 0)
	{
		write(2, "free: error: double free\n", 26);
		exit(EXIT_FAILURE);
	}
	while (temp != NULL)
	{
		if (ptr == temp->ptr)
		{
			//delete node here
			//this is really sloppy "deletion" but ok for now
			if (prev != NULL)
				prev->next = temp->next;
			if (ft_lstsize(&g_alloc_lst) == 0)
				g_alloc_lst = NULL;
			printf("removed entry of size %ld with address %p\n", temp->alloc_size, ptr);//////////
			return (temp->alloc_size);
		}
		prev = temp;
		temp = temp->next;
	}
	return (0);
}

int	update_alloc_lst(size_t size, void *ptr, bool method)
{

	if (method == ADD_ENTRY)
		update_alloc_lst_add(size, ptr);
	else if (method == RM_ENTRY)
		return (update_alloc_lst_rm(ptr));
	return (0);
}