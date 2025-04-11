#include "cub3d.h"

void calc_hit_distance(t_game *game, bool is_wall_hit, )
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
	double	xa;
	double	ya;
	double	nxt_xstep;
	double	nxt_ystep;
	double	hit_x;
	double	hit_y;
	double	verif;
	bool	hit_wall;

	hit_wall = false;
	ya = floor(game->player.y / TILE) * TILE;
	if (is_down(angle))
		ya += TILE;
	xa = game->player.x + ((ya - game->player.y) / tan(angle));
	ystep = TILE;
	if (is_up(angle))
		ystep *= -1;
	xstep = TILE / tan(angle);
	if (is_left(angle) && xstep > 0)
		xstep *= -1;
	if (is_right(angle) && xstep < 0)
		xstep *= -1;
	nxt_xstep = xa;
	nxt_ystep = ya;
	verif = nxt_ystep;
	while (nxt_xstep >= 0 && (int)floor(nxt_xstep / TILE) <= 25
		&& nxt_ystep >= 0 && (int)floor(nxt_ystep / TILE) <= 9)
	{
		if (is_up(angle))
			verif = nxt_ystep - 1;
		else
			verif = nxt_ystep;
		if (is_a_wall(game->game_info->map, nxt_xstep, verif))
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

}


void	check_intersections(t_game *game, double angle, int x)
{
	horizontal_intersection(game, angle);
	vertical_intersection(game, angle);
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
	// Déterminer la face du mur touchée
	if (game->raycast_info.v_hit_dist > game->raycast_info.h_hit_dist)
	// Si l'intersection horizontale est la plus proche
	{
		if (sin(angle) > 0)
		{
			render_3d_map(game, game->NO_data, x);
			game->raycast_info.color = 0xFF0000;
		}
		else
		{
			render_3d_map(game, game->SO_data, x);
			game->raycast_info.color = 0x00FF00;
		}
	}
	else // Sinon, l'intersection verticale est la plus proche
	{
		if (cos(angle) > 0)
		{
			render_3d_map(game, game->WE_data, x);
			game->raycast_info.color = 0x0000FF;
		}
		else
		{
			render_3d_map(game, game->EA_data, x);
			game->raycast_info.color = 0xFFA500;
		}
	}
}
