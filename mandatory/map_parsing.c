/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knavarre <knavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 12:45:40 by knavarre          #+#    #+#             */
/*   Updated: 2025/04/14 14:13:06 by knavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_map_lines(char *line, t_game_info *data)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' '))
		i++;
	if (line[i] == '\n' || line[i] == '\0')
		data->lock_valid_map_lines = 1;
	while (line[i])
	{
		if (line[i] == 'N' || line[i] == 'E'
			|| line[i] == 'W' || line[i] == 'S')
		{
			if (data->lock_NEWS == 1)
				return (printf("Error : duplicates [N,E,W,S]\n"), ERROR);
			data->lock_NEWS = 1;
		}
		else if (line[i] != '1' && line[i] != '0' && line[i] != 'W'
			&& line[i] != 'E' && line[i] != 'N' && line[i] != 'S'
			&& line[i] != ' ')
			return (printf("Error : other [0,1,N,E,W,S] in the map.\n"), ERROR);
		else if (data->lock_valid_map_lines == 1)
			return (printf("Error : map separate by line empty.\n"), ERROR);
		i++;
	}
	return (SUCCESS);
}

int	check_map(char **map, int x, int y)
{
	while (map[x])
	{
		y = 0;
		while (map[x][y])
		{
			if (map[x][y] == '0' || map[x][y] == 'N' || map[x][y] == 'S'
				|| map[x][y] == 'E' || map[x][y] == 'W')
			{
				if (x == 0 || !map[x - 1] || !map[x - 1][y] || map[x - 1][y] == ' ')
					return (printf("Error: map invalid.\n"), ERROR);
				else if (!map[x + 1] || !map[x + 1][y] || map[x + 1][y] == ' ')
					return (printf("Error: map invalid2.\n"), ERROR);
				else if (!map[x] || !map[x][y + 1] || map[x][y + 1] == ' ')
					return (printf("Error: map invalid3.\n"), ERROR);
				else if (y == 0 || !map[x] || !map[x][y - 1] || map[x][y - 1] == ' ')
					return (printf("Error: map invalid4.\n"), ERROR);
			}
			y++;
		}
		x++;
	}
	return (SUCCESS);
}

int	error_checking_list_size(int *len, t_list *tmp, t_game_info *data)
{
	(*len) = 0;
	while (tmp != NULL)
	{
		(*len)++;
		if (is_valid_map_lines(tmp->content, data) != SUCCESS)
			return (ERROR);
		tmp = tmp->next;
	}
	if (data->lock_NEWS != 1)
		return (printf("Error: no [N,E,W,S].\n"), ERROR);
	return (SUCCESS);
}

int	transforms_list_to_tab(t_game_info *data)
{
	t_list	*tmp;
	int		len_list;
	int		i;

	tmp = data->map_list;
	i = 0;
	if (error_checking_list_size(&len_list, tmp, data) != SUCCESS)
		return (ERROR);
	data->map = (char **)malloc(sizeof(char *) * (len_list + 1));
	if (!data->map)
		return (ERROR);
	tmp = data->map_list;
	while (tmp != NULL)
	{
		data->map[i] = ft_strdup(tmp->content);
		if (!data->map[i])
			return (ERROR);
		tmp = tmp->next;
		i++;
	}
	data->map[i] = NULL;
	if (check_map(data->map, 0, 0) != SUCCESS)
		return (ERROR);
	return (SUCCESS);
}

/*****************************************************************************/

int	map_after_textures(t_game_info *data)
{
	if (data->north_texture == NULL || data->south_texture == NULL
		|| data->west_texture == NULL
		|| data->east_texture == NULL
		|| data->floor_color[0] == -1
		|| data->ceiling_color[0] == -1)
	{
		printf("Error : map before instructions or incorrect line detected.\n");
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
