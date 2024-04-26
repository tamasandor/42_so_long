NAME = libftprintf.a
CC = cc
FLAGS = -Wall -Werror -Wextra
AR = ar -rcs
SRC = ft_print.c ft_printf.c ft_conversions.c

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	$(MAKE) -C ./libft
	cp libft/libft.a $(NAME)
	$(AR) $(NAME) $(OBJ)

all: $(NAME)

clean:
	$(MAKE) fclean -C ./libft
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re