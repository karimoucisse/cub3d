/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knavarre <knavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 13:42:11 by knavarre          #+#    #+#             */
/*   Updated: 2025/04/16 13:07:52 by knavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	close_door_at(t_game *game, double x, double y)
{
	int	map_x = (int)(x / TILE);
	int	map_y = (int)(y / TILE);

	if (map_x < 0 || map_y < 0 || map_y >= game->game_info->map_height || map_x >= game->game_info->map_widht)
		return ;
	if (game->game_info->map[map_y][map_x] == 'O')
		game->game_info->map[map_y][map_x] = 'D';
}

void	open_door_at(t_game *game, double x, double y)
{
	int	map_x = (int)(x / TILE);
	int	map_y = (int)(y / TILE);

	if (map_x < 0 || map_y < 0 || map_y >= game->game_info->map_height || map_x >= game->game_info->map_widht)
		return ;
	if (game->game_info->map[map_y][map_x] == 'D')
		game->game_info->map[map_y][map_x] = 'O';
}

void	open_doors_in_radius(t_game *game, double radius)
{
	int px = game->player.x / TILE;
	int py = game->player.y / TILE;

	int min_x = fmax(px - 3, 0);
	int max_x = fmin(px + 3, game->game_info->map_widht - 1);
	int min_y = fmax(py - 3, 0);
	int max_y = fmin(py + 3, game->game_info->map_height - 1);

	for (int y = min_y; y <= max_y; y++)
	{
		for (int x = min_x; x <= max_x; x++)
		{
			double world_x = x * TILE + TILE / 2;
			double world_y = y * TILE + TILE / 2;
			double dx = world_x - game->player.x;
			double dy = world_y - game->player.y;
			double dist = sqrt(dx * dx + dy * dy);
			if (dist <= radius * TILE && game->game_info->map[y][x] == 'D')
				open_door_at(game, x * TILE, y * TILE);
			else if (dist > 3 * TILE && game->game_info->map[y][x] == 'O')
				close_door_at(game, x * TILE, y * TILE);
		}
	}
}

void	move_forward(t_game *game)
{
	double	x_cpy;
	double	y_cpy;
	double	speed;

	speed = MOVE_SPEED;
	if (game->player.sprint)
		speed = SPRINT;
	x_cpy = game->player.x + cos(game->player.rot_angle) * (speed
			+ COLLISION_OFFSET);
	y_cpy = game->player.y + sin(game->player.rot_angle) * (speed
			+ COLLISION_OFFSET);
	if (!is_a_wall(game, x_cpy, game->player.y, NULL))
		game->player.x = game->player.x + cos(game->player.rot_angle) * speed;
	if (!is_a_wall(game, game->player.x, y_cpy, NULL))
		game->player.y = game->player.y + sin(game->player.rot_angle) * speed;
	open_doors_in_radius(game, 3);
}

void	move_right(t_game *game)
{
	double	x_cpy;
	double	y_cpy;
	double	speed;

	speed = MOVE_SPEED;
	if (game->player.sprint)
		speed = SPRINT;
	x_cpy = game->player.x - sin(game->player.rot_angle) * (speed
			+ COLLISION_OFFSET);
	y_cpy = game->player.y + cos(game->player.rot_angle) * (speed
			+ COLLISION_OFFSET);
	if (!is_a_wall(game, x_cpy, game->player.y, NULL))
		game->player.x = game->player.x - sin(game->player.rot_angle) * speed;
	if (!is_a_wall(game, game->player.x, y_cpy, NULL))
		game->player.y = game->player.y + cos(game->player.rot_angle) * speed;
	open_doors_in_radius(game, 3);
}

void	move_left(t_game *game)
{
	double	x_cpy;
	double	y_cpy;
	double	speed;

	speed = MOVE_SPEED;
	if (game->player.sprint)
		speed = SPRINT;
	x_cpy = game->player.x + sin(game->player.rot_angle) * (speed
			+ COLLISION_OFFSET);
	y_cpy = game->player.y - cos(game->player.rot_angle) * (speed
			+ COLLISION_OFFSET);
	if (!is_a_wall(game, x_cpy, game->player.y, NULL))
		game->player.x = game->player.x + sin(game->player.rot_angle) * speed;
	if (!is_a_wall(game, game->player.x, y_cpy, NULL))
		game->player.y = game->player.y - cos(game->player.rot_angle) * speed;
	open_doors_in_radius(game, 3);
}

void	move_backward(t_game *game)
{
	double	x_cpy;
	double	y_cpy;
	double	speed;

	speed = MOVE_SPEED;
	if (game->player.sprint)
		speed = SPRINT;
	x_cpy = game->player.x - cos(game->player.rot_angle) * (speed
			+ COLLISION_OFFSET);
	y_cpy = game->player.y - sin(game->player.rot_angle) * (speed
			+ COLLISION_OFFSET);
	if (!is_a_wall(game, x_cpy, game->player.y, NULL))
		game->player.x = game->player.x - cos(game->player.rot_angle) * speed;
	if (!is_a_wall(game, game->player.x, y_cpy, NULL))
		game->player.y = game->player.y - sin(game->player.rot_angle) * speed;
	open_doors_in_radius(game, 3);
}

void	move_player(t_game *game)
{
	double	rot_speed;

	rot_speed = ROTATION_SPEED;
	if (game->player.sprint)
		rot_speed = FAST_ROTATION;
	if (game->player.right_rotate)
		game->player.rot_angle += rot_speed;
	if (game->player.left_rotate)
		game->player.rot_angle -= rot_speed;
	if (game->player.key_up)
		move_forward(game);
	if (game->player.key_down)
		move_backward(game);
	if (game->player.key_right)
		move_right(game);
	if (game->player.key_left)
		move_left(game);
	clear_map(game);
}
