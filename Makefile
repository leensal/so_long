NAME = so_long
FILES = main.c read_map.c clean_up.c movement.c count_objects.c
EXC = so_long
OBJS = $(FILES:.c=.o)
CC = cc	
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
LIBFT = libft/libft.a
MLX = mlx/libmlx.a

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) libft/libft.a -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(EXC)

$(LIBFT):
	make -C libft

$(MLX):
	make -C mlx

clean:
	(cd libft && make clean)
	(cd mlx && make clean)
	rm -f $(OBJS)

fclean: clean
	(cd libft && make fclean)
	rm -f $(EXC)

re: fclean all

.PHONY: all clean fclean re