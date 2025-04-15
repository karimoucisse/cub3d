/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:52:09 by kcisse            #+#    #+#             */
/*   Updated: 2025/04/16 00:16:04 by kcisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_map_square(int x, int y, int color, t_game *game)
{
	int	i;

	i = 0;
	while (i < MINIMAP_TILE)
	{
		ft_put_pixel(x + i, y, color, game);
		ft_put_pixel(x + i, y + MINIMAP_TILE, color, game);
		ft_put_pixel(x, y + i, color, game);
		ft_put_pixel(x + MINIMAP_TILE, y + i, color, game);
		i++;
	}
}

void	draw_player(int x, int y, int color, t_game *game)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		ft_put_pixel(x + i, y, color, game);
		ft_put_pixel(x + i, y + 2, color, game);
		ft_put_pixel(x, y + i, color, game);
		ft_put_pixel(x + 2, y + i, color, game);
		i++;
	}
}

void	create_map(t_game *game)
{
	int		i;
	int		j;
	char	**map;

	i = 0;
	map = game->game_info->map;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '1')
				draw_map_square(j * MINIMAP_TILE, i * MINIMAP_TILE, 0xFFFF0000,
					game);
			j++;
		}
		i++;
	}
}

void	draw_ray(t_game *game, double angle)
{
	int		i;
	double	x;
	double	y;

	i = 0;
	while (1)
	{
		x = (game->player.x / TILE * MINIMAP_TILE) + cos(angle) * i;
		y = (game->player.y / TILE * MINIMAP_TILE) + sin(angle) * i;
		i++;
		if ((is_left(angle) && is_a_wall(game, ((x - 1) / MINIMAP_TILE * TILE),
					y / MINIMAP_TILE * TILE)))
			break ;
		if ((is_up(angle) && is_a_wall(game, x / MINIMAP_TILE * TILE, ((y - 1)
						/ MINIMAP_TILE * TILE))))
			break ;
		if (is_a_wall(game, x / MINIMAP_TILE * TILE, y / MINIMAP_TILE * TILE))
			break ;
		if (is_right(angle) && ((int)x / MINIMAP_TILE
				* TILE) >= (int)game->raycast_info.wall_hitx)
			break ;
		ft_put_pixel(x, y, 0xFFFFF0, game);
	}
}

void	minimap(t_game *game)
{
	double	x;
	double	y;

	create_map(game);
	x = game->player.x / TILE * MINIMAP_TILE;
	y = game->player.y / TILE * MINIMAP_TILE;
	draw_player(x, y, 0, game);
}
