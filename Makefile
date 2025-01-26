.PHONY: all re clean fclean

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

# I added -fPIC (in short, I can use your functions memory safely in my code and simultaneously)
CFLAGS = -Wall -Wextra -Werror -g -fPIC

NAME := libft_malloc_$(HOSTTYPE).so
LINK := libft_malloc.so

SRC = malloc.c \
		free.c \
		realloc.c \
		utils.c

OBJ = $(SRC:.c=.o)

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

all: lft $(NAME) $(LINK)

lft:
	make -C libft/
	make -C libft/ bonus

$(NAME): $(OBJ)
	gcc -shared -o $(NAME) $(OBJ) libft/libft.a $(CFLAGS)

$(LINK): $(NAME)
	ln -sf $(NAME) $(LINK)

clean:
	make -C libft/ clean
	rm -rf $(OBJ)

fclean: clean
	make -C libft/ fclean
	rm -rf $(NAME) $(LINK)
	rm -f a.out

re: fclean all