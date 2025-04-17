/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knavarre <knavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 12:45:40 by knavarre          #+#    #+#             */
/*   Updated: 2025/04/17 15:35:02 by knavarre         ###   ########.fr       */
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
		if (line[i] == 'N' || line[i] == 'E' || line[i] == 'W'
			|| line[i] == 'S')
		{
			if (data->lock_news == 1)
				return (printf("Error\nduplicates [N,E,W,S]\n"), ERROR);
			data->lock_news = 1;
		}
		else if (line[i] != '1' && line[i] != '0' && line[i] != 'W'
			&& line[i] != 'E' && line[i] != 'N' && line[i] != 'S'
			&& line[i] != ' ')
			return (printf("Error\nother [0,1,N,E,W,S].\n"), ERROR);
		else if (data->lock_valid_map_lines == 1)
			return (printf("Error\nmap separate by line empty.\n"), ERROR);
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
				if (x == 0 || !map[x - 1] || !map[x - 1][y] || map[x
					- 1][y] == ' ')
					return (printf("Error\nmap invalid.\n"), ERROR);
				else if (!map[x + 1] || !map[x + 1][y] || map[x + 1][y] == ' ')
					return (printf("Error\nmap invalid2.\n"), ERROR);
				else if (!map[x] || !map[x][y + 1] || map[x][y + 1] == ' ')
					return (printf("Error\nmap invalid3.\n"), ERROR);
				else if (y == 0 || !map[x] || !map[x][y - 1] || map[x][y
					- 1] == ' ')
					return (printf("Error\nmap invalid4.\n"), ERROR);
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
	if (data->lock_news != 1)
		return (printf("Error\nno [N,E,W,S].\n"), ERROR);
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
