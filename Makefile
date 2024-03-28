NAME = so_long
CC = cc
FLAGS = -Wall -Werror -Wextra
SRC = src/error.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C include/libft
	mv include/libft/libft.a ./libft.a
	$(CC) $(FLAGS) $(OBJ) libft.a -o $(NAME)

clean:
	$(MAKE) -C include/libft clean
	rm -f $(OBJ) libft.a

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re