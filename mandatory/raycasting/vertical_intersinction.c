#include "cub3d.h"

void	vertical_intersection(t_game *game, double angle)
{
	double	xstep;
	double	ystep;
	double	xa;
	double	ya;
	double	nxt_xstep;
	double	nxt_ystep;
	double	hit_x;
	double	hit_y;
	double	verif;
	bool	hit_wall;

	hit_wall = false;
	xa = floor(game->player.x / TILE) * TILE;
	if (is_right(angle))
		xa += TILE;
	ya = game->player.y + ((xa - game->player.x) * tan(angle));
	xstep = TILE;
	if (is_left(angle))
		xstep *= -1;
	ystep = TILE * tan(angle);
	if (is_up(angle) && ystep > 0)
		ystep *= -1;
	if (is_down(angle) && ystep < 0)
		ystep *= -1;
	nxt_xstep = xa;
	nxt_ystep = ya;
	verif = nxt_xstep;
	hit_x = 0;
	hit_y = 0;
	while (nxt_xstep >= 0 && (int)floor(nxt_xstep / TILE) <= 25
		&& nxt_ystep >= 0 && (int)floor(nxt_ystep / TILE) <= 9)
	{
		if (is_left(angle))
			verif = nxt_xstep - 1;
		else
			verif = nxt_xstep;
		if (is_a_wall(game->game_info->map, verif, nxt_ystep))
		{
			hit_wall = true;
			hit_x = nxt_xstep;
			hit_y = nxt_ystep;
			break ;
		}
		else
		{
			nxt_xstep += xstep;
			nxt_ystep += ystep;
		}
	}
	if (hit_wall)
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
