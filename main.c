/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsahloul <lsahloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 18:45:46 by lsahloul          #+#    #+#             */
/*   Updated: 2025/07/17 21:46:16 by lsahloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_image(t_game *game, int i, int j)
{
	if (game->map[j][i] == '1')
		mlx_put_image_to_window(game->mlx, game->win,
			game->imgs->water, i * 16, j * 16);
	else
		mlx_put_image_to_window(game->mlx, game->win,
			game->imgs->grass, i * 16, j * 16);
	if (game->map[j][i] == 'C')
		mlx_put_image_to_window(game->mlx, game->win,
			game->imgs->apple1, i * 16, j * 16);
	if (game->map[j][i] == 'E')
		mlx_put_image_to_window(game->mlx, game->win,
			game->imgs->exit, i * 16, j * 16);
	else if (game->map[j][i] == 'P')
	{
		game->player_pos[0] = i;
		game->player_pos[1] = j;
		mlx_put_image_to_window(game->mlx, game->win,
			game->imgs->kitty, i * 16, j * 16);
	}
}

void	render(t_game *game)
{
	int	i;
	int	j;

	j = -1;
	mlx_clear_window(game->mlx, game->win);
	while (++j < game->row_count)
	{
		i = -1;
		while (++i < game->column_count)
		{
			put_image(game, i, j);
		}
	}
}

void	load_images(void *mlx, t_game *game)
{
	int	width;
	int	height;

	game->imgs->apple1 = mlx_xpm_file_to_image(mlx, "textures/apple1.xpm",
			&width, &height);
	if (!game->imgs->apple1)
		murder(game, "Couldn't load image: apple1\n");
	game->imgs->grass = mlx_xpm_file_to_image(mlx, "textures/grass.xpm",
			&width, &height);
	if (!game->imgs->grass)
		murder(game, "Couldn't load image: grass\n");
	game->imgs->kitty = mlx_xpm_file_to_image(mlx, "textures/kitty.xpm",
			&width, &height);
	if (!game->imgs->kitty)
		murder(game, "Couldn't load image: kitty\n");
	game->imgs->water = mlx_xpm_file_to_image(mlx, "textures/water.xpm",
			&width, &height);
	if (!game->imgs->water)
		murder(game, "Couldn't load image: water\n");
	game->imgs->exit = mlx_xpm_file_to_image(mlx, "textures/exit.xpm",
			&width, &height);
	if (!game->imgs->exit)
		murder(game, "Couldn't load image: exit\n");
}

void	init(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		murder(game, "MLX failed to load\n");
	game->win = mlx_new_window(game->mlx, 16 * (game->column_count),
			16 * (game->row_count), "Kawaiiiii game");
	if (!game->win)
		murder(game, "MLX window failed to load\n");
	load_images(game->mlx, game);
}

int	main(int argc, char **argv)
{
	t_imgs		imgs;
	t_game		game;

	if (argc != 2)
	{
		ft_printf("Usage: ./so_long <map_file>\n");
		return (1);
	}
	game.fruit_count = 0;
    game.fruit_pos = NULL;
	game.mlx = NULL;
	game.win = NULL;
	game.movement_count = 0;
	imgs = (t_imgs){0};
	game.imgs = &imgs;
	read_map(&game, argv[1]);
	position_saver(&game);
	init(&game);
	check_path(&game);
	render(&game);
	mlx_key_hook(game.win, &key_hook_function, &game);
	mlx_hook(game.win, ON_DESTROY, 0, &on_destroy, &game);
	mlx_loop(game.mlx);
	return (0);
}
