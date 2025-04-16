/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3draycasting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:52:38 by kcisse            #+#    #+#             */
/*   Updated: 2025/04/16 10:53:42 by kcisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_map(t_game *game, t_texture texture, int x)
{
	int		y;
	double	wall_bottom_pixel;
	double	wall_top_pixel;

	wall_top_pixel = put_ceiling_pixel(game, x);
	wall_bottom_pixel = put_floor_pixel(game, x);
	y = wall_top_pixel;
	while (y < wall_bottom_pixel)
	{
		put_wall_pixel(game, texture, y, x);
		y++;
	}
}

void	check_intersections_bonus(t_game *game, double angle, int x, bool minimap)
{
	double	project_plane;

	horizontal_intersection(game, angle);
	vertical_intersection(game, angle);
	calc_ray_distance(game, angle);
	project_plane = (WIDTH / 2) / tan((FOV * (PI / 180)) / 2);
	game->raycast_info.wall_height = (TILE / game->raycast_info.wall_hit_dist)
		* project_plane;
	if (!minimap)
	{
		if (!game->raycast_info.was_hit_vertical)
		{
			if (sin(angle) > 0)
				render_map(game, game->so_data, x);
			else
				render_map(game, game->no_data, x);
		}
		else
		{
			if (cos(angle) > 0)
				render_map(game, game->we_data, x);
			else
				render_map(game, game->ea_data, x);
		}
	}
}

void	raycast_3d(t_game *game)
{
	int		i;
	double	angle;

	move_player(game);
	i = 0;
	angle = game->player.rot_angle - ((FOV * (PI / 180)) / 2);
	while (i < WIDTH)
	{
		check_intersections_bonus(game, normalize_angle(angle), i, false);
		angle += (FOV * (PI / 180)) / WIDTH;
		i++;
	}
	minimap(game);
	mlx_put_image_to_window(game->mlx_ptr, game->mlx_win, game->img_ptr, 0, 0);
}
