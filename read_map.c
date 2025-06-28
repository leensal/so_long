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

void read_map(t_game *game)
{
    (void)game;
    char *file;

    int fd = open("map.ber", O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening map file");
        exit(EXIT_FAILURE);
    }
    
    file = read_file(fd);
    printf("Reading map...\n");
    printf("%s\n", file);
}