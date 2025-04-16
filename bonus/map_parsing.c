/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knavarre <knavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 12:45:40 by knavarre          #+#    #+#             */
/*   Updated: 2025/04/16 13:04:33 by knavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_after_textures(t_game_info *data)
{
	if (data->north_texture == NULL || data->south_texture == NULL
		|| data->west_texture == NULL || data->east_texture == NULL
		|| data->door_texture == NULL || data->floor_color[0] == -1
		|| data->ceiling_color[0] == -1)
	{
		printf("Error\nmap before instructions or incorrect line detected.\n");
		return (ERROR);
	}
	return (SUCCESS);
}

int	map_parsing(char *line, t_game_info *data)
{
	t_list	*new_node;
	char	*new_line;
	int		len;

	new_node = NULL;
	new_line = NULL;
	len = ft_strlen(line);
	data->lock = 1;
	if (map_after_textures(data) != SUCCESS)
		return (ERROR);
	if (line[len - 1] == '\n')
		new_line = ft_strndup(line, len - 1);
	else
		new_line = ft_strndup(line, len);
	if (!new_line)
		return (ERROR);
	new_node = ft_lstnew(new_line);
	if (!new_node)
		return (ERROR);
	ft_lstadd_back(&data->map_list, new_node);
	return (SUCCESS);
}
