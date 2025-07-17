/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsahloul <lsahloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 18:56:58 by lsahloul          #+#    #+#             */
/*   Updated: 2025/07/17 22:51:42 by lsahloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
void	move(t_game *game, int x, int y)
{
	if (game->map[game->player_pos[1] + y][game->player_pos[0] + x] == '1')
		return ;
	if (game->map[game->player_pos[1] + y][game->player_pos[0] + x] == 'C')
	{
		game->fruit_count++;
		ft_printf(" \n FRUIT COUNT: %d \n", game->fruit_count);
	}
	if (game->map[game->player_pos[1] + y][game->player_pos[0] + x] == 'E')
	{
		ft_printf(" \n FRUIT COUNT: %d \n other fruit: %d\n", game->fruit_count, game->counters.fruit_count);
        if (game->fruit_count != game->counters.fruit_count)
            return;
		ft_printf("MOVEMENT COUNT: %d \n", game->movement_count + 1);
		murder(game, NULL);
	}
	game->map[game->player_pos[1]][game->player_pos[0]] = '0';
	game->player_pos[0] += x;
	game->player_pos[1] += y;
	game->map[game->player_pos[1]][game->player_pos[0]] = 'P';
	game->movement_count++;
	ft_printf(" \n MOVEMENT COUNT: %d \n", game->movement_count);
	render(game);
}

int	key_hook_function(int key, void *s)
{
	t_game	*game;

	game = s;
	if (key == 0)
		move(game, -1, 0);
	else if (key == 13)
		move(game, 0, -1);
	else if (key == 1)
		move(game, 0, 1);
	else if (key == 2)
		move(game, 1, 0);
	else if (key == 53)
		on_destroy(s);
	return (0);
}

void print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
}

int	find_path(t_game *game, int x, int y, int end)
{
	
	if (y < 0 || y >= game->column_count || x < 0 || x >= game->row_count)
		return (0);
	if (game->map[x][y] == end)
		return (1);
	if (game->map[x][y] == '1'
		|| game->map[x][y] == 'V' || game->map[x][y] == 'E')
		return (0);
	print_map(game->map);
	game->map[x][y] = 'V';
	if (find_path(game, x, y + 1, end) == 1)
		return (1);
	if (find_path(game, x + 1, y, end) == 1)
		return (1);
	if (find_path(game, x, y - 1, end) == 1)
		return (1);
	if (find_path(game, x - 1, y, end) == 1)
		return (1);

	return (0);
}

void	reset_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	game->map[game->player_pos[0]][game->player_pos[1]] = 'P'; // [i][j]
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'V')
				game->map[i][j] = '0';
			j++;
		}
		i++;
	}
}

void	check_path(t_game *game)
{
	int	i;

	if (find_path(game, game->player_pos[0], game->player_pos[1], 'E') == 0) // [i][j] 
		murder(game, "Error: No path to exit\n");
	
	i = -1;
	while (++i < game->counters.fruit_count)
	{
		reset_map(game);
		if (find_path(game, game->fruit_pos[i].x, game->fruit_pos[i].y, 'P') == 0) // [i][j]
			murder(game, "Error: No path to fruit\n");
	}
	i = -1;
	while (++i < game->counters.fruit_count)
		game->map[game->fruit_pos[i].x][game->fruit_pos[i].y] = 'C';
}
