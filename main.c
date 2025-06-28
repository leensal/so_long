#include "mlx/mlx.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define ON_DESTROY 17

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

void render(t_game *game){
    int i=0;
    int j=0;
    while(j<3){
        i = 0;
        while (i < 5){
            if (game->map[j][i]== '1'){
                mlx_put_image_to_window(game->mlx, game->win, game->imgs->water, i*16, j*16);
            }
            else if (game->map[j][i]== '0'){
                mlx_put_image_to_window(game->mlx, game->win, game->imgs->grass, i*16, j*16);
            }
            else if(game->map[j][i]== 'C')
            {
                mlx_put_image_to_window(game->mlx, game->win, game->imgs->apple1, i*16, j*16);
            }
            else if(game->map[j][i]== 'P')
            {
                game->player_pos[0] = i;
                game->player_pos[1] = j;
                mlx_put_image_to_window(game->mlx, game->win, game->imgs->grass, i*16, j*16);
                mlx_put_image_to_window(game->mlx, game->win, game->imgs->kitty, i*16, j*16);
            }
            i++;
        }
        j++;

    }
}

void load_images(void *mlx, t_imgs *imgs)
{
    int     width;
    int     height;

    imgs->apple1 = mlx_xpm_file_to_image(mlx, "images/apple1.xpm", &width, &height);
    imgs->apple2 = mlx_xpm_file_to_image(mlx, "images/apple2.xpm", &width, &height);
    imgs->apple3 = mlx_xpm_file_to_image(mlx, "images/apple3.xpm", &width, &height);
    imgs->grass = mlx_xpm_file_to_image(mlx, "images/grass.xpm", &width, &height);
    imgs->kitty = mlx_xpm_file_to_image(mlx, "images/kitty.xpm", &width, &height);
    imgs->water = mlx_xpm_file_to_image(mlx, "images/water.xpm", &width, &height);
}

int on_destroy(void *s){
    exit(7);
    return 0;
}

// void move(t_game *game, int x, int y){
//     game->map[game->player_pos[1]][game->player_pos[0]] = '0';
//     game->player_pos[0] += x;
//     game->player_pos[1] += y;
//     game->map[game->player_pos[1]][game->player_pos[0]] = 'P';
//     render(game);
    
// }

int key_hook_function(int key, void *s){
    t_game *game;

    game = s;

    if (key == 0){
        // move(game, -1, 0);
    }
    else if (key == 13){
        // move(game, 0, -1);
    }
    else if (key == 1){
        // move(game, 0, 1);
    }
    else if (key == 2){
        // move(game, 1, 0);
    }
    else if(key== 53){
        on_destroy(s);
    }

    printf("%d \n", key);
return 0;
}

char **read_map(t_game *game){
    return NULL;
}

int main(void){
    void	*mlx;
    void	*mlx_win;
    void	*img;
    int		img_width;
	int		img_height;
    t_imgs  imgs;
    t_game game;

    char *static_map[4] = {
        "11111",
        "10P01",
        "11111"
    };

    for (int i = 0; i < 3; i++) {
        game.map[i] = static_map[i];
    }
    game.map[3] = NULL; // Null-terminate the map array
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, (16*5), (16*3), "Hello world!");
    load_images(mlx, &imgs);
    game.imgs = &imgs;
    game.mlx = mlx;
    game.win = mlx_win;
    render(&game);

    mlx_key_hook(mlx_win, &key_hook_function, &game);
    mlx_hook(mlx_win, ON_DESTROY, 0, &on_destroy, &game);
	mlx_loop(mlx);
    return 0;
}