/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knavarre <knavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 13:14:38 by knavarre          #+#    #+#             */
/*   Updated: 2025/04/18 13:26:48 by knavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_file_name(char *file_name)
{
	int	len;

	len = ft_strlen(file_name);
	if (len < 4)
		return (0);
	if (file_name[len - 1] != 'b' || file_name[len - 2] != 'u')
		return (0);
	if (file_name[len - 3] != 'c' || file_name[len - 4] != '.')
		return (0);
	if (file_name[len - 5] == '/' || file_name[len - 5] == ' ')
		return (0);
	return (1);
}

int	parsing(char *line, t_game_info *data)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] && ft_strncmp(line + i, "NO", 2) == 0)
		return (textures_function(&data->north_texture, line, i));
	else if (line[i] && ft_strncmp(line + i, "SO", 2) == 0)
		return (textures_function(&data->south_texture, line, i));
	else if (line[i] && ft_strncmp(line + i, "WE", 2) == 0)
		return (textures_function(&data->west_texture, line, i));
	else if (line[i] && ft_strncmp(line + i, "EA", 2) == 0)
		return (textures_function(&data->east_texture, line, i));
	else if (line[i] && ft_strncmp(line + i, "DO", 2) == 0)
		return (textures_function(&data->door_texture, line, i));
	else if (line[i] && line[i + 1] && line[i] == 'F'
		&& (line[i + 1] == ' ' || line[i + 1] == '\t'))
		return (colors_function(&data->floor_color, line + i + 1));
	else if (line[i] && line[i + 1] && line[i] == 'C'
		&& (line[i + 1] == ' ' || line[i + 1] == '\t'))
		return (colors_function(&data->ceiling_color, line + i + 1));
	else if (line[i] && line[i] == '\n' && data->lock == 0)
		return (SUCCESS);
	else
		return (map_parsing(line, data));
}

int	opening_parsing(t_game_info *data, char *str)
{
	int		file;
	char	*line;

	line = NULL;
	file = open(str, O_RDONLY);
	if (file == -1)
	{
		printf("Error\nopening file %s\n", str);
		return (ERROR);
	}
	line = get_next_line(file, 0);
	while (line != NULL)
	{
		if (parsing(line, data) != SUCCESS)
			return (get_next_line(file, 1), ft_free(&line), close(file), ERROR);
		ft_free(&line);
		line = get_next_line(file, 0);
	}
	if (transforms_list_to_tab(data) != SUCCESS)
		return (ERROR);
	return (close(file), SUCCESS);
}
