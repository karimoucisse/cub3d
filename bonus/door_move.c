/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_mouve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:02:57 by kcisse            #+#    #+#             */
/*   Updated: 2025/04/16 15:32:39 by kcisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	close_door_at(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)(x / TILE);
	map_y = (int)(y / TILE);
	if (map_x < 0 || map_y < 0 || map_y >= game->game_info->map_height
		|| map_x >= game->game_info->map_widht)
		return ;
	if (game->game_info->map[map_y][map_x] == 'O')
		game->game_info->map[map_y][map_x] = 'D';
}

void	open_door_at(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)(x / TILE);
	map_y = (int)(y / TILE);
	if (map_x < 0 || map_y < 0 || map_y >= game->game_info->map_height
		|| map_x >= game->game_info->map_widht)
		return ;
	if (game->game_info->map[map_y][map_x] == 'D')
		game->game_info->map[map_y][map_x] = 'O';
}

void	handle_door_at(t_game *game, int x, int y, double radius)
{
	double	world_x;
	double	world_y;
	double	dx;
	double	dy;
	double	dist;

	world_x = x * TILE + TILE / 2;
	world_y = y * TILE + TILE / 2;
	dx = world_x - game->player.x;
	dy = world_y - game->player.y;
	dist = sqrt(dx * dx + dy * dy);
	if (dist <= radius * TILE && game->game_info->map[y][x] == 'D')
		open_door_at(game, x * TILE, y * TILE);
	else if (dist > 3 * TILE && game->game_info->map[y][x] == 'O')
		close_door_at(game, x * TILE, y * TILE);
}

void	open_doors_in_radius(t_game *game, double radius)
{
	int	max_x;
	int	min_y;
	int	max_y;
	int	x;
	int	y;

	max_x = fmin((game->player.x / TILE) + 3, game->game_info->map_widht - 1);
	min_y = fmax((game->player.y / TILE) - 3, 0);
	max_y = fmin((game->player.y / TILE) + 3, game->game_info->map_height - 1);
	y = min_y;
	while (y <= max_y)
	{
		x = fmax((game->player.x / TILE) - 3, 0);
		while (x <= max_x)
		{
			handle_door_at(game, x, y, radius);
			x++;
		}
		y++;
	}
}
