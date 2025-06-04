#include "mlx/mlx.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct  s_imgs
{
    void *apple1;
    void *apple2;
    void *apple3;
    void *grass;
    void *kitty;
    void *water;
} t_imgs;


typedef struct s_main
{
    t_imgs *imgs;
    void *mlx;
    void *win;
    char map[3][5];
} t_main;


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

int key_hook(int key, void *s){
    t_main *main;

    main = s;

    if (key == 0){

    }
    else if (key == 13){

    }
    else if (key == 2){

    }
    else if(key== 1){

    }
    else if(key== 53){
        on_destroy(s);
    }

    printf("%d \n", key);
return 0;
}

void render(t_main *main){
    int i=0;
    int j=0;
    while(j<3){
        i = 0;
        while (i < 5){
            if (main->map[j][i]== '1'){
                mlx_put_image_to_window(main->mlx, main->win, main->imgs->water, i*16, j*16);
            }
            else if (main->map[j][i]== '0'){
                mlx_put_image_to_window(main->mlx, main->win, main->imgs->grass, i*16, j*16);
            }
            else if(main->map[j][i]== 'C')
            {
                mlx_put_image_to_window(main->mlx, main->win, main->imgs->apple1, i*16, j*16);
            }
            else if(main->map[j][i]== 'P')
            {
                mlx_put_image_to_window(main->mlx, main->win, main->imgs->grass, i*16, j*16);
                mlx_put_image_to_window(main->mlx, main->win, main->imgs->kitty, i*16, j*16);
            }
            i++;
        }
        j++;

    }
}

char **read_map(t_main *main){
    

}

int main(){
    void	*mlx;
    void	*mlx_win;
    void	*img;
    int		img_width;
	int		img_height;
    t_imgs  imgs;
    t_main main;

    char static_map[3][5] = {
        {'1','1','1','1','1'},
        {'1','0','P','0','1'},
        {'1','1','1','1','1'}
    };
    main.map = static_map;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, (16*5), (16*3), "Hello world!");
    int i=0;
    int j=0;
    load_images(mlx, &imgs);
    render(&main);


    main.imgs = &imgs;
    main.mlx = mlx;
    main.win = mlx_win;
    mlx_key_hook(mlx_win, &key_hook, &main);
    mlx_hook(mlx_win, 17, 0, &on_destroy, &main);
	mlx_loop(mlx);
    return 0;
}