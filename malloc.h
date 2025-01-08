#ifndef MALLOC_H
#define MALLOC_H

#define TINY_ALLOC 16
#define SMALL_ALLOC 128

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

void	show_alloc_mem();
void	*malloc(size_t size);
void	free(void *ptr);
void	*realloc(void *ptr, size_t size);

#endif
