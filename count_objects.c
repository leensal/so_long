/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsahloul <lsahloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:39:51 by lsahloul          #+#    #+#             */
/*   Updated: 2025/07/19 19:11:36 by lsahloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	save_position(t_game *game, int i, int j, int *fruit_index)
{
	if (game->map[i][j] == 'C')
		game->fruit_pos[(*fruit_index)++] = (t_position){i, j};
	else if (game->map[i][j] == 'E')
	{
		game->exit_pos[0] = i;
		game->exit_pos[1] = j;
	}
	else if (game->map[i][j] == 'P')
	{
		game->player_pos[0] = i;
		game->player_pos[1] = j;
	}
}

void	position_saver(t_game *game)
{
	int	i;
	int	j;
	int	fruit_index;

	i = -1;
	fruit_index = 0;
	game->fruit_pos = malloc(sizeof(t_position) * game->counters.fruit_count);
	if (!game->fruit_pos)
		murder(game, "Error allocating memory for fruit positions");
	while (game->map[++i])
	{
		j = -1;
		while (game->map[i][++j])
		{
			save_position(game, i, j, &fruit_index);
		}
	}
}
