.PHONY: all re clean fclean

NAME = libft_malloc{REPLACE THIS}.so

SRC = malloc.c \
	  free.c \
	  realloc.c

#prob doesn't work, can't remember makefile
OBJ = $(SRC).c=.o

all: $(NAME)
	gcc -Wall -Wextra -Werror $(SRC) -o $(NAME)

$(NAME): $(OBJ)
