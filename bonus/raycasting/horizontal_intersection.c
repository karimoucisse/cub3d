/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_intersection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knavarre <knavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:42:21 by kcisse            #+#    #+#             */
/*   Updated: 2025/04/16 12:25:37 by knavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_h_hit_distance(t_game *game, bool is_wall_hit, double hit_x,
		double hit_y)
{
	if (is_wall_hit)
	{
		game->raycast_info.h_hit_posx = hit_x;
		game->raycast_info.h_hit_posy = hit_y;
		game->raycast_info.h_hit_dist = calc_dist(game->player.x,
				game->player.y, hit_x, hit_y);
		game->raycast_info.was_hit_vertical = false;
	}
	else
		game->raycast_info.h_hit_dist = __INT_MAX__;
}

void	calc_next_h_point(t_game *game, double angle, double *nxt_x_point,
		double *nxt_y_point)
{
	*nxt_y_point = floor(game->player.y / TILE) * TILE;
	if (is_down(angle))
		*nxt_y_point += TILE;
	*nxt_x_point = game->player.x + ((*nxt_y_point - game->player.y)
			/ tan(angle));
}

void	calc_h_steps(double angle, double *xstep, double *ystep)
{
	*ystep = TILE;
	if (is_up(angle))
		*ystep *= -1;
	*xstep = TILE / tan(angle);
	if (is_left(angle) && *xstep > 0)
		*xstep *= -1;
	if (is_right(angle) && *xstep < 0)
		*xstep *= -1;
}

void	horizontal_intersection(t_game *game, double angle)
{
	double	xstep;
	double	ystep;
	double	nxt_x_point;
	double	nxt_y_point;
	bool	hit_wall;

	xstep = 0;
	ystep = 0;
	nxt_x_point = 0;
	nxt_y_point = 0;
	hit_wall = false;
	calc_next_h_point(game, angle, &nxt_x_point, &nxt_y_point);
	calc_h_steps(angle, &xstep, &ystep);
	while (nxt_x_point >= 0 && nxt_y_point >= 0)
	{
		if ((is_up(angle) && is_a_wall(game, nxt_x_point, nxt_y_point - 1, &game->raycast_info.hit_type_horizontal))
			|| (!is_up(angle) && is_a_wall(game, nxt_x_point, nxt_y_point, &game->raycast_info.hit_type_horizontal)))
		{
			hit_wall = true;
			break ;
		}
		nxt_x_point += xstep;
		nxt_y_point += ystep;
	}
	calc_h_hit_distance(game, hit_wall, nxt_x_point, nxt_y_point);
}
