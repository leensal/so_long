up:
	(cd mlx && make)
	(cd libft && make)
	cc read_map.c main.c clean_up.c libft/libft.a mlx/libmlx.a -g -fsanitize=address -Lmlx -lmlx -framework OpenGL -framework AppKit