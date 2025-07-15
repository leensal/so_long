#include "so_long.h"

void render(t_game *game){
	int i = 0;
	int j = 0;
	
	mlx_clear_window(game->mlx, game->win);
	while(j<game->row_count)
	{
		i = 0;
		while (i < game->column_count){
			if (game->map[j][i]== '1')
				mlx_put_image_to_window(game->mlx, game->win, game->imgs->water, i*16, j*16);
			else
				mlx_put_image_to_window(game->mlx, game->win, game->imgs->grass, i*16, j*16);
			if(game->map[j][i]== 'C')
				mlx_put_image_to_window(game->mlx, game->win, game->imgs->apple1, i*16, j*16);
			if(game->map[j][i]== 'E')
				mlx_put_image_to_window(game->mlx, game->win, game->imgs->exit, i*16, j*16);
			else if(game->map[j][i]== 'P')
			{
				game->player_pos[0] = i;
				game->player_pos[1] = j;
				mlx_put_image_to_window(game->mlx, game->win, game->imgs->kitty, i*16, j*16);
			}
			i++;
		}
		j++;
	}
}

void load_images(void *mlx, t_game *game)
{
	int     width;
	int     height;

	game->imgs->apple1 = mlx_xpm_file_to_image(mlx, "images/apple1.xpm", &width, &height);
	if (!game->imgs->apple1)
		murder(game, "Couldn't load image: apple1\n");
	game->imgs->grass = mlx_xpm_file_to_image(mlx, "images/grass.xpm", &width, &height);
	if (!game->imgs->grass)
		murder(game, "Couldn't load image: grass\n");
	game->imgs->kitty = mlx_xpm_file_to_image(mlx, "images/kitty.xpm", &width, &height);
	if (!game->imgs->kitty)
		murder(game, "Couldn't load image: kitty\n");
	game->imgs->water = mlx_xpm_file_to_image(mlx, "images/water.xpm", &width, &height);
	if (!game->imgs->water)
		murder(game, "Couldn't load image: water\n");
	game->imgs->exit = mlx_xpm_file_to_image(mlx, "images/exit.xpm", &width, &height);
	if (!game->imgs->exit)
		murder(game, "Couldn't load image: exit\n");
}

void move(t_game *game, int x, int y)
{
	if (game->map[game->player_pos[1]+y][game->player_pos[0]+x] == '1')
		return;
	if (game->map[game->player_pos[1]+y][game->player_pos[0]+x] == 'C')
	{
		game->fruit_count++;
		ft_printf(" \n FRUIT COUNT: %d \n",game->fruit_count );
	}
	if (game->map[game->player_pos[1]+y][game->player_pos[0]+x] == 'E')
	{
		ft_printf("MOVEMENT COUNT: %d \n",game->movement_count+1);
		murder(game, NULL);
	}
	game->map[game->player_pos[1]][game->player_pos[0]] = '0';
	game->player_pos[0] += x;
	game->player_pos[1] += y;
	game->map[game->player_pos[1]][game->player_pos[0]] = 'P';
	game->movement_count++;
	ft_printf(" \n MOVEMENT COUNT: %d \n",game->movement_count );
	render(game);
}

int key_hook_function(int key, void *s)
{
	t_game *game;

	game = s;

	if (key == 0)
		move(game, -1, 0);
	else if (key == 13)
		move(game, 0, -1);
	else if (key == 1)
		move(game, 0, 1);
	else if (key == 2)
		move(game, 1, 0);
	else if(key== 53)
		on_destroy(s);
	return (0);
}

void	init(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->mlx = mlx_init();
	if (!game->mlx)
		murder(game, "MLX failed to load\n");
	game->win = mlx_new_window(game->mlx, 16*(game->column_count), 16*(game->row_count), "Kawaiiiii game");
	if (!game->win)
		murder(game, "MLX window failed to load\n");
	load_images(game->mlx, game);
}

int main(int argc, char ** argv)
{
	void	*img;
	int		img_width;
	int		img_height;
	t_imgs	imgs;
	t_game	game;

	game.fruit_count = 0;
	game.movement_count = 0;
	imgs = (t_imgs){0};
	game.imgs = &imgs;
	read_map(&game, argv[1]);
	init(&game);
	render(&game);
	mlx_key_hook(game.win, &key_hook_function, &game);
	mlx_hook(game.win, ON_DESTROY, 0, &on_destroy, &game);
	mlx_loop(game.mlx);
	return (0);
}
