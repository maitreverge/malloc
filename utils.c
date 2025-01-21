#include "malloc.h"

/*
*	Adds padding to the block if necessary, and returns the new allocation
*/
void	*calc_alignment_padding(t_alloc_list *node)
{
	if (node != NULL && node->ptr + node->alloc_size % WORD_SIZE != 0)
		return ((node->ptr + node->alloc_size) + ((size_t)(node->ptr + node->alloc_size) % WORD_SIZE));
	return (node->ptr + node->alloc_size);
}

/*
*	Yes, there's an overhead to the subfunctions, 
*	but it looks way better than crunching them both into update_alloc_lst()
*/

static void update_alloc_lst_add(size_t size, void *ptr, u_int64_t *g_alloc_lst_size)
{
	t_alloc_list *new = NULL;

	for (t_alloc_list *t = g_alloc_lst; t != NULL; t = t->next)
	{
		if (t->ptr == NULL)
		{
			new = t;
			break ;
		}
	}
	if (new == NULL)
	{
		//haven't implemented yet, rm printf+exit once it is
		// get_new_alloc_lst_nodes(&new);
		printf("UH OH\n");
		exit(EXIT_FAILURE);
	}
	new->alloc_size = size;
	new->ptr = ptr;
	if (g_alloc_lst == NULL || *g_alloc_lst_size == 0)
		g_alloc_lst = new;
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
			printf("removed entry of size %ld with address %p\n", temp->alloc_size, ptr);//////////
			//not sure about this. i'm assuming that allocations
			//within the zones marked as freed are just reset to default
			temp->alloc_size = 0;
			temp->ptr = NULL;
			if (prev != NULL)
				prev->next = temp->next;
			return (temp->alloc_size);
		}
		prev = temp;
		temp = temp->next;
	}
	(*g_alloc_lst_size)--;
	return (0);
}

/*
*	'size' is the size of the allocation
*	'ptr' is the pointer to the memory that was allocated (malloc()), or to be deallocated (free())
*	'method' determines whether the alloc list will be expanded, or shortened.
*	'g_alloc_lst_size' is a pointer to the size of the alloc list. free() passes NULL instead.
*
*
*	'nullcase_ptr' points to the real g_alloc_lst_size.
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