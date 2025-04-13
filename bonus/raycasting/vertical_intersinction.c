#include "cub3d.h"

void	calc_v_hit_distance(t_game *game, bool is_wall_hit, double hit_x,
		double hit_y)
{
	if (is_wall_hit)
	{
		game->raycast_info.v_hit_posx = hit_x;
		game->raycast_info.v_hit_posy = hit_y;
		game->raycast_info.v_hit_dist = calc_dist(game->player.x,
				game->player.y, hit_x, hit_y);
		game->raycast_info.was_hit_vertical = true;
	}
	else
		game->raycast_info.v_hit_dist = __INT_MAX__;
}

void	vertical_intersection(t_game *game, double angle)
{
	double	xstep;
	double	ystep;
	double	nxt_xstep;
	double	nxt_ystep;
	double	verif;
	bool	hit_wall;

	hit_wall = false;
	nxt_xstep = floor(game->player.x / TILE) * TILE;
	if (is_right(angle))
		nxt_xstep += TILE;
	nxt_ystep = game->player.y + ((nxt_xstep - game->player.x) * tan(angle));
	xstep = TILE;
	if (is_left(angle))
		xstep *= -1;
	ystep = TILE * tan(angle);
	if (is_up(angle) && ystep > 0)
		ystep *= -1;
	if (is_down(angle) && ystep < 0)
		ystep *= -1;
	verif = nxt_xstep;
	while (nxt_xstep >= 0 && nxt_ystep >= 0)
	{
		if (is_left(angle))
			verif = nxt_xstep - 1;
		else
			verif = nxt_xstep;
		if (is_a_wall(game, verif, nxt_ystep))
		{
			hit_wall = true;
			break ;
		}
		nxt_xstep += xstep;
		nxt_ystep += ystep;
	}
	calc_v_hit_distance(game, hit_wall, nxt_xstep, nxt_ystep);
}
