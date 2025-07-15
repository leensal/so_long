#include "so_long.h"

char	*read_file(int fd)
{
	char	buf[BUFFER_SIZE + 1];
	char	*full;
	char	*temp;
	ssize_t	red;

	full = NULL;
	red = read(fd, buf, BUFFER_SIZE);
	while (red > 0)
	{
		buf[red] = 0;
		if (full)
		{
			temp = full;
			full = ft_strjoin(full, buf);
			free(temp);
		}
		else
			full = ft_strdup(buf);
		red = read(fd, buf, BUFFER_SIZE);
	}
	return (full);
}

void	validate_rows(t_game *game, char *file)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(file[i])
	{
		if (file[i]== '\n' && file[i+1] && file[i+1] == '\n')
		{
			free(file);
			murder(game, "Error opening map file");
		}
		i++;
	}
}

void count_objects(t_game *game, int x, t_counters *count){
	if (x == 'C')
		count->fruit_count++;
	else if (x == 'E')
		count->exit_count++;
	else if (x == 'P')
		count->player_count++;
	else if (x != 'P' && x != '0' && x != '1' && x != 'C' && x != 'E'){
		murder(game, "Error opening map file");	
	}
}

void validate_columns(t_game *game){
	int i;
	int j;
	t_counters counter;
	(void)game;

	i = -1;
	counter = (t_counters){0};
	while(game->map[++i])
	{
		j = 0;
		while(game->map[i][j]){
			count_objects(game, game->map[i][j], &counter);
			if ((i == 0 || i == game->row_count-1) && game->map[i][j] != '1')
				murder(game, "Error reading map file\n");
			j++;
		}
		if (game->map[i][0] != '1' || game->map[i][game->column_count-1] != '1')
			murder(game, "Error reading map file\n");
	}
	if (counter.exit_count != 1 || counter.fruit_count == 0 || counter.player_count != 1)
		murder(game, "Error reading map file\n");
}

void read_map(t_game *game, char *map_name)
{
    char *file;
    int i;
	int current;

    i = 0;
    int fd = open(map_name, O_RDONLY);
    if (fd < 0)
        murder(game, "Error opening map file");
    file = read_file(fd);
    close(fd);
    if (!file)
        murder(game, "Error reading map file\n");
	validate_rows(game, file);
    game->map = ft_split(file, '\n');
    free(file);
	if (!game->map)
		murder(game, "split fails");
    while (game->map[i])
    {
		current = ft_strlen(game->map[i]);
		if(game->map[i+1] && current != ft_strlen(game->map[i+1]))
			murder(game, "Error reading map file\n");
		i++;
    }
	game->column_count = current ;
	game->row_count = i;
	validate_columns(game);
}
