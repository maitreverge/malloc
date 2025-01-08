.PHONY: all re clean fclean

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

CFLAGS = -Wall -Wextra -Werror -g

NAME = libft_malloc_$(HOSTTYPE).so

SRC = malloc.c \
	  free.c \
	  realloc.c

#prob doesn't work, can't remember makefile
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	gcc -Wall -Wextra -Werror $(SRC) -o $(NAME) $(CFLAGS)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all