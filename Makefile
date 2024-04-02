NAME = so_long
CC = cc
FLAGS = -Wall -Werror -Wextra
GET_NEXT_LINE = include/get_next_line/get_next_line.c include/get_next_line/get_next_line_utils.c
SRC = src/error.c $(GET_NEXT_LINE) src/utils.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C include/libft
	mv include/libft/libft.a ./libft.a
	$(CC) $(FLAGS) $(OBJ) libft.a -o $(NAME)
	@rm libft.a

clean:
	$(MAKE) -C include/libft clean
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re