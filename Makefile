.PHONY: all re clean fclean

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

CFLAGS = -Wall -Wextra -Werror -g

NAME = libft_malloc_$(HOSTTYPE).so

SRC = malloc.c 
	#   free.c \
	#   realloc.c

#prob doesn't work, can't remember makefile
OBJ = $(SRC:.c=.o)

all: lft $(NAME)

lft:
	make -C libft/ bonus

$(NAME): $(OBJ)
	gcc $(SRC) -o $(NAME) libft/libft.a $(CFLAGS)

clean:
	make -C libft/ clean
	rm -rf $(OBJ)

fclean: clean
	make -C libft/ fclean
	rm -rf $(NAME)

re: fclean all