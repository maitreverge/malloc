#include "malloc.h"

/*
*	Yes, there's an overhead to the subfunctions, 
*	but it looks way better than crunching them both into update_alloc_lst()
*/

static void update_alloc_lst_add(size_t size, void *ptr, u_int64_t *g_alloc_lst_size)
{
	t_alloc_list *new = NULL;
	t_alloc_list *temp;

	if (!(new = malloc(sizeof(t_alloc_list))))//not allowed to use malloc, but for testing purposes this is okay
		exit(EXIT_FAILURE);
	new->alloc_size = size;
	new->ptr = ptr;
	new->next = NULL;
	if (g_alloc_lst == NULL || ft_lstsize((t_list *)&g_alloc_lst) == 0)
		g_alloc_lst = new;
	else
	{
		temp = (t_alloc_list *)ft_lstlast((t_list *)g_alloc_lst);
		temp->next = new;
	}
	(*g_alloc_lst_size)++;
	printf("added entry of size %ld with address %p\n", size, ptr);//////////
}

static int update_alloc_lst_rm(void *ptr, u_int64_t *g_alloc_lst_size)
{
	t_alloc_list *prev = NULL;
	t_alloc_list *temp = g_alloc_lst;

	if (g_alloc_lst == NULL || g_alloc_lst_size == NULL || *g_alloc_lst_size == 0)
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
			if (*g_alloc_lst_size == 0)
				g_alloc_lst = NULL;
			printf("removed entry of size %ld with address %p\n", temp->alloc_size, ptr);//////////
			return (temp->alloc_size);
		}
		prev = temp;
		temp = temp->next;
	}
	(*g_alloc_lst_size)--;
	return (0);
}

/*
*	nullcase_ptr points to the real g_alloc_lst_size.
*	This allows us to use the real value of g_alloc_lst_size,
*		since free() passes NULL.
*/
int	update_alloc_lst(size_t size, void *ptr, bool method, u_int64_t *g_alloc_lst_size)
{
	static u_int64_t	*nullcase_ptr = NULL;

	if (method == ADD_ENTRY)
	{
		nullcase_ptr = g_alloc_lst_size;
		update_alloc_lst_add(size, ptr, g_alloc_lst_size);
	}
	else if (method == RM_ENTRY)
		return (update_alloc_lst_rm(ptr, nullcase_ptr));
	return (0);
}