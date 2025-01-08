#ifndef MALLOC_H
#define MALLOC_H

#define PAGESIZE sysconf(_SC_PAGESIZE)
#define SMALL_ALLOC PAGESIZE
#define MEDIUM_ALLOC PAGESIZE * 5
#define ADD_ENTRY 1
#define RM_ENTRY 0


#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <sys/resource.h>
#include "libft/libft.h"

typedef struct s_alloc_list
{
	size_t	alloc_size;
	void	*ptr;
	struct s_alloc_list	*next;
}	t_alloc_list;

t_alloc_list	*g_alloc_lst = NULL;

void	show_alloc_mem();
void	*my_malloc(size_t size);
void	my_free(void *ptr);
void	*my_realloc(void *ptr, size_t size);

#endif
