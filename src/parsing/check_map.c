#include "cub3d.h"

int	check_map_content(char **map)
{
	int	i;
	int	dirrection;
	int	j;

	i = 0;
	dirrection = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!ft_strchr("01 NSEW", map[i][j]))
				return (0);
			if (ft_strchr("NSEW", map[i][j]))
				dirrection++;
			j++;
		}
		i++;
	}
	if (dirrection > 1)
		return (0);
	return (1);
}
int	check_map_wall(char **map, int map_height)
{
	int	i;

	i = 0;
	while (map[0][i])
	{
		if (map[0][i] != '1')
			return (0);
		i++;
	}
	i = 0;
	while (map[map_height - 1][i])
	{
		if (map[map_height - 1][i] != '1')
			return (0);
		i++;
	}
	i = -1;
	while (map[++i])
	{
		if (map[i][0] != '1')
			return (0);
		if (map[i][ft_strlen(map[i] - 1)] != '1')
			return (0);
	}
	return (1);
}

char	**parse_map(int fd, char *line)
{
	int		direction;
	char	**map;
	int		len;
	int		map_height;
	int		map_max_width;

	map = malloc(sizeof(char *) * MAX_MAP_SIZE);
	map_height = 0;
	len = 0;
	while (line)
	{
		ft_trim(line);
		if (ft_strlen(line) != 0)
		{
			map_height++;
			map[len] = ft_strdup(line);
			len++;
		}
		free(line);
		line = get_next_line(fd, 0);
	}
	if (!check_map_content(map))
		return (0);
	if (!check_map_wall(map, map_height))
		return (0);
	return (map);
}
