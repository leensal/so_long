up:
	cc main.c mlx/libmlx.a -g -fsanitize=address -Lmlx -lmlx -framework OpenGL -framework AppKit