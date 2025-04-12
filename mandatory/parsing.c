/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knavarre <knavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 13:14:38 by knavarre          #+#    #+#             */
/*   Updated: 2025/04/12 13:14:57 by knavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parsing(char *line, t_game_info *data)
{
	int		i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] && line[i + 1] && line[i] == 'N' && line[i + 1] == 'O')
		return (textures_function(&data->north_texture, line, i));
	else if (line[i] && line[i + 1] && line[i] == 'S' && line[i + 1] == 'O')
		return (textures_function(&data->south_texture, line, i));
	else if (line[i] && line[i + 1] && line[i] == 'W' && line[i + 1] == 'E')
		return (textures_function(&data->west_texture, line, i));
	else if (line[i] && line[i + 1] && line[i] == 'E' && line[i + 1] == 'A')
		return (textures_function(&data->east_texture, line, i));
	else if (line[i] && line[i] == 'F')
		return (colors_function(&data->floor_color, line + i + 1));
	else if (line[i] && line[i] == 'C')
		return (colors_function(&data->ceiling_color, line + i + 1));
	else if (line[i] && line[i] == '\n' && data->lock == 0)
		return (SUCCESS);
	else
		return (map_parsing(line, data));
	return (SUCCESS);
}

int	opening_parsing(t_game_info *data, char *str)
{
	int		file;
	char	*line;

	line = NULL;
	file = open(str, O_RDONLY);
	if (file == -1)
	{
		printf("Error opening file %s\n", str);
		return (ERROR);
	}
	line = get_next_line(file);
	while (line != NULL)
	{
		if (parsing(line, data) != SUCCESS)
			return (ft_free(&line), close(file), ERROR);
		ft_free(&line);
		line = get_next_line(file);
	}
	if (transforms_list_to_tab(data) != SUCCESS)
		return (ERROR);
	return (close(file), SUCCESS);
}
