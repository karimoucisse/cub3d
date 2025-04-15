/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 13:42:11 by knavarre          #+#    #+#             */
/*   Updated: 2025/04/15 16:05:25 by kcisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	if (!is_a_wall(game, x_cpy, game->player.y))
		game->player.x = game->player.x + cos(game->player.rot_angle) * speed;
	if (!is_a_wall(game, game->player.x, y_cpy))
		game->player.y = game->player.y + sin(game->player.rot_angle) * speed;
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
	if (!is_a_wall(game, x_cpy, game->player.y))
		game->player.x = game->player.x - sin(game->player.rot_angle) * speed;
	if (!is_a_wall(game, game->player.x, y_cpy))
		game->player.y = game->player.y + cos(game->player.rot_angle) * speed;
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
	if (!is_a_wall(game, x_cpy, game->player.y))
		game->player.x = game->player.x + sin(game->player.rot_angle) * speed;
	if (!is_a_wall(game, game->player.x, y_cpy))
		game->player.y = game->player.y - cos(game->player.rot_angle) * speed;
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
	if (!is_a_wall(game, x_cpy, game->player.y))
		game->player.x = game->player.x - cos(game->player.rot_angle) * speed;
	if (!is_a_wall(game, game->player.x, y_cpy))
		game->player.y = game->player.y - sin(game->player.rot_angle) * speed;
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
