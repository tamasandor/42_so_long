NAME = so_long
CC = cc
FLAGS = -Wall -Werror -Wextra
SRC = error.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C ../libft
	mv ../libft/libft.a ./libft.a
	$(CC) $(FLAGS) $(OBJ) libft.a -o $(NAME)

clean:
	$(MAKE) -C ../libft clean
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME) libft.a

re: fclean all

.PHONY: all clean fclean re