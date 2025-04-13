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
void	horizontal_intersection(t_game *game, double angle)
{
	double	xstep;
	double	ystep;
	double	nxt_xstep;
	double	nxt_ystep;
	double	verif;
	bool	hit_wall;

	hit_wall = false;
	nxt_ystep = floor(game->player.y / TILE) * TILE;
	if (is_down(angle))
		nxt_ystep += TILE;
	nxt_xstep = game->player.x + ((nxt_ystep - game->player.y) / tan(angle));
	ystep = TILE;
	if (is_up(angle))
		ystep *= -1;
	xstep = TILE / tan(angle);
	if (is_left(angle) && xstep > 0)
		xstep *= -1;
	if (is_right(angle) && xstep < 0)
		xstep *= -1;
	verif = nxt_ystep;
	while (nxt_xstep >= 0 && nxt_ystep >= 0)
	{
		if (is_up(angle))
			verif = nxt_ystep - 1;
		else
			verif = nxt_ystep;
		if (is_a_wall(game, nxt_xstep, verif))
		{
			hit_wall = true;
			break ;
		}
		nxt_xstep += xstep;
		nxt_ystep += ystep;
	}
	calc_h_hit_distance(game, hit_wall, nxt_xstep, nxt_ystep);
}

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
void	check_intersections(t_game *game, double angle, int x)
{
	horizontal_intersection(game, angle);
	vertical_intersection(game, angle);
	calc_ray_distance(game, angle);
	if (!game->raycast_info.was_hit_vertical)
	{
		if (sin(angle) > 0)
			render_3d_map(game, game->SO_data, x);
		else
			render_3d_map(game, game->NO_data, x);
	}
	else
	{
		if (cos(angle) > 0)
			render_3d_map(game, game->WE_data, x);
		else
			render_3d_map(game, game->EA_data, x);
	}
}
