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
    char **map;
    game->map = map;
}