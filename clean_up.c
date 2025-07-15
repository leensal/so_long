#include "so_long.h"

void destroy_image(t_game *game)
{
    if (game->imgs->apple1)
        mlx_destroy_image(game->mlx, game->imgs->apple1);
    if (game->imgs->exit)
        mlx_destroy_image(game->mlx, game->imgs->exit);
    if (game->imgs->grass)
        mlx_destroy_image(game->mlx, game->imgs->grass);
    if (game->imgs->kitty)
        mlx_destroy_image(game->mlx, game->imgs->kitty);
    if (game->imgs->water)
        mlx_destroy_image(game->mlx, game->imgs->water);
}

void free_split(char **s)
{
    int i;

    i = 0;
    while(s[i]){
        free(s[i]);
        i++;
    }
    free(s);
}

void murder(t_game *game, const char * s)
{
    destroy_image(game);
    if (game->mlx && game->win)
    {
        mlx_destroy_window(game->mlx, game->win);
        free(game->mlx);
    }
    free_split(game->map);
    if (s)
        perror(s);
    exit(EXIT_FAILURE);
}

int	on_destroy(void *game)
{
	murder((t_game *)game, NULL);
	return (0);
}
