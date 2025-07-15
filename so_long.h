#ifndef SO_LONG_H
# define SO_LONG_H

#include "mlx/mlx.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include "libft/libft.h"

# define ON_DESTROY 17
# define BUFFER_SIZE 42

typedef struct s_imgs
{
    void *apple1;
    void *grass;
    void *kitty;
    void *water;
    void *exit;
}   t_imgs;

typedef struct s_game
{
    t_imgs *imgs;
    void *mlx;
    void *win;
    char **map;
    int player_pos[2];
    int column_count;
    int row_count;
    int fruit_count;
    int movement_count;
} t_game;

typedef struct s_counters
{
	int player_count;
	int	exit_count;
	int	fruit_count;
} t_counters;

char    *read_file(int fd);
void    read_map(t_game *game, char * map);
void    murder(t_game *game, const char *s);
int     on_destroy(void *game);
void    destroy_image(t_game *game);

#endif
