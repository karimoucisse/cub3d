/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knavarre <knavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 13:44:22 by knavarre          #+#    #+#             */
/*   Updated: 2025/04/16 12:28:19 by knavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	rgb_to_int(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

int	is_a_wall(t_game *game, double x, double y, int *door)
{
	int	x_block;
	int	y_block;
	int	map_height;

	x_block = floor(x / TILE);
	y_block = floor(y / TILE);
	map_height = game->game_info->map_height;
	if (door)
		*door = 0;
	if (y_block < 0 || y_block >= map_height)
		return (1);
	if (!game->game_info->map[y_block])
		return (1);
	if (x_block < 0 || x_block >= (int)strlen(game->game_info->map[y_block]))
		return (1);
	if (game->game_info->map[y_block][x_block] == '1' || game->game_info->map[y_block][x_block] == ' ')
		return (1);
	if (game->game_info->map[y_block][x_block] == 'D')
	{
		if (door)
			*door = 1;
		return (1);
	}	
	return (0);
}

void	clear_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			ft_put_pixel(j, i, 0, game);
			j++;
		}
		i++;
	}
}
