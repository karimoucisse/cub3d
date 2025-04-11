#include "cub3d.h"

int	check_is_valid_color(char **colors, int *texture_var)
{
	int	i;
	int	color_num;
	int	j;

	i = -1;
	color_num = -1;
	if (ft_tab_len(colors) != 3)
		return (0);
	while (colors[++i])
	{
		j = -1;
		ft_trim(colors[i]);
		if ((int)ft_strlen(colors[i]) == 0)
			return (0);
		while (colors[i][j++])
		{
			if (!ft_strchr("0123456789", colors[i][j]))
				return (0);
		}
		if (colors[i] == NULL)
			return (0);
		color_num = ft_atoi(colors[i]);
		if (color_num < 0 || color_num > 255)
			return (0);
		texture_var[i] = color_num;
	}
	return (1);
}
int	parse_color(char *str, int *texture_var)
{
	char	**colors;
	int		i;
	int		count;

	i = -1;
	count = 0;
	while (texture_var[++i])
	{
		if (texture_var[i] != -1)
			return (0);
	}
	i = -1;
	while (str[i++])
	{
		if (str[i] == ',')
		{
			if (i == 0 || i == ft_strlen(str) - 1)
				return (0);
			count++;
		}
	}
	if (count != 2)
		return (0);
	colors = ft_split(str, ',');
	if (!check_is_valid_color(colors, texture_var))
		return (0);
	return (1);
}

int	parse_texture(char *str, t_game_info *info)
{
	int	return_val;

	return_val = 1;
	if (!ft_strncmp(str, "NO ", 3) && !info->north_texture)
		return_val = file_exist(str + 3, &info->north_texture);
	else if (!ft_strncmp(str, "SO ", 3) && !info->south_texture)
		return_val = file_exist(str + 3, &info->south_texture);
	else if (!ft_strncmp(str, "EA ", 3) && !info->east_texture)
		return_val = file_exist(str + 3, &info->east_texture);
	else if (!ft_strncmp(str, "WE ", 3) && !info->west_texture)
		return_val = file_exist(str + 3, &info->west_texture);
	else if (!ft_strncmp(str, "F ", 2))
		return_val = parse_color(str + 2, info->floor_color);
	else if (!ft_strncmp(str, "C ", 2))
		return_val = parse_color(str + 2, info->ceiling_color);
	else
		return_val = 0;
	return (return_val);
}

int	check_texture(t_game_info *info)
{
	int	i;

	i = -1;
	if (!info->north_texture || !info->south_texture)
		return (0);
	if (!info->west_texture || !info->east_texture)
		return (0);
	while (i++ < 3)
	{
		if (info->floor_color[i] == -1)
			return (0);
		if (info->ceiling_color[i] == -1)
			return (0);
	}
	return (1);
}
