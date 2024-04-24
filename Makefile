NAME = so_long
CC = cc
FLAGS = -Wall -Werror -Wextra
GET_NEXT_LINE = include/get_next_line/get_next_line.c include/get_next_line/get_next_line_utils.c
SRC = src/error.c $(GET_NEXT_LINE) src/utils.c src/map_check.c src/game.c src/render.c src/movements.c
OBJ = $(SRC:.c=.o)
MLX_DIR = ./mlx-linux
MLX = $(MLX_DIR)/libmlx.a

all: $(NAME)

$(NAME): $(OBJ) $(MLX)
	$(MAKE) -C include/libft
	mv include/libft/libft.a ./libft.a
	$(CC) $(FLAGS) $(OBJ) libft.a $(MLX) -lX11 -lXext -o $(NAME)
	@rm libft.a

$(MLX):
	$(MAKE) -C $(MLX_DIR)

clean:
	@$(MAKE) -C include/libft clean
	@$(MAKE) -C $(MLX_DIR) clean
	@rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re