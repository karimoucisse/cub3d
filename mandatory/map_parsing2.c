/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 12:45:40 by knavarre          #+#    #+#             */
/*   Updated: 2025/04/16 12:48:21 by kcisse           ###   ########.fr       */
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
				return (print_error("Error : duplicates [N,E,W,S]\n"));
			data->lock_news = 1;
		}
		else if (line[i] != '1' && line[i] != '0' && line[i] != 'W'
			&& line[i] != 'E' && line[i] != 'N' && line[i] != 'S'
			&& line[i] != ' ')
			return (print_error("Error : other [0,1,N,E,W,S] in the map.\n"));
		else if (data->lock_valid_map_lines == 1)
			return (print_error("Error : map separate by line empty.\n"));
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
					return (print_error("Error: map invalid.\n"));
				else if (!map[x + 1] || !map[x + 1][y] || map[x + 1][y] == ' ')
					return (print_error("Error: map invalid2.\n"));
				else if (!map[x] || !map[x][y + 1] || map[x][y + 1] == ' ')
					return (print_error("Error: map invalid3.\n"));
				else if (y == 0 || !map[x] || !map[x][y - 1] || map[x][y
					- 1] == ' ')
					return (print_error("Error: map invalid4.\n"));
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
		return (print_error("Error: no [N,E,W,S].\n"));
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
