/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 13:14:38 by knavarre          #+#    #+#             */
/*   Updated: 2025/04/16 11:27:42 by kcisse           ###   ########.fr       */
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
		return (print_error("Error opening file %s\n"));
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
