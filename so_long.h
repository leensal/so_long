#ifndef SO_LONG_H
# define SO_LONG_H

#include "mlx/mlx.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
# define BUFFER_SIZE 42
#include <string.h>
#include "libft/libft.h"

typedef struct  s_imgs
{
    void *apple1;
    void *apple2;
    void *apple3;
    void *grass;
    void *kitty;
    void *water;
} t_imgs;


typedef struct s_game
{
    t_imgs *imgs;
    void *mlx;
    void *win;
    char *map[4];
    int player_pos[2];
} t_game;

char	*read_file(int fd);
void read_map(t_game *game);

#endif