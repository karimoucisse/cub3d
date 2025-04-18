/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:41:49 by kcisse            #+#    #+#             */
/*   Updated: 2025/04/14 16:42:24 by kcisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_ray_distance(t_game *game, double angle)
{
	game->raycast_info.was_hit_vertical = false;
	if (game->raycast_info.v_hit_dist < game->raycast_info.h_hit_dist)
	{
		game->raycast_info.was_hit_vertical = true;
		game->raycast_info.wall_hit_dist = game->raycast_info.v_hit_dist
			* cos(angle - game->player.rot_angle);
		game->raycast_info.wall_hitx = game->raycast_info.v_hit_posx;
		game->raycast_info.wall_hity = game->raycast_info.v_hit_posy;
	}
	else
	{
		game->raycast_info.wall_hit_dist = game->raycast_info.h_hit_dist
			* cos(angle - game->player.rot_angle);
		game->raycast_info.wall_hitx = game->raycast_info.h_hit_posx;
		game->raycast_info.wall_hity = game->raycast_info.h_hit_posy;
	}
}

int	get_xcord(t_game *game)
{
	int	texture_offset_x;

	if (game->raycast_info.was_hit_vertical)
		texture_offset_x = (int)game->raycast_info.wall_hity % TILE;
	else
		texture_offset_x = (int)game->raycast_info.wall_hitx % TILE;
	return (texture_offset_x);
}

double	normalize_angle(double angle)
{
	angle = fmod(angle, 2 * PI);
	if (angle < 0)
		angle += 2 * PI;
	return (angle);
}

double	puissance2(double val)
{
	return (val * val);
}

double	calc_dist(double x1, double y1, double x2, double y2)
{
	return (sqrt(puissance2(x2 - x1) + puissance2(y2 - y1)));
}
