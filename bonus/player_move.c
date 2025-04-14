/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 13:42:11 by knavarre          #+#    #+#             */
/*   Updated: 2025/04/14 13:54:10 by kcisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_game *game)
{
	double	x_cpy;
	double	y_cpy;

	x_cpy = game->player.x + cos(game->player.rot_angle)
		* (SPRINT(game->player.sprint) + COLLISION_OFFSET);
	y_cpy = game->player.y + sin(game->player.rot_angle)
		* (SPRINT(game->player.sprint) + COLLISION_OFFSET);
	if (!is_a_wall(game, x_cpy, game->player.y))
		game->player.x = game->player.x + cos(game->player.rot_angle)
			* SPRINT(game->player.sprint);
	if (!is_a_wall(game, game->player.x, y_cpy))
		game->player.y = game->player.y + sin(game->player.rot_angle)
			* SPRINT(game->player.sprint);
}

void	move_right(t_game *game)
{
	double	x_cpy;
	double	y_cpy;

	x_cpy = game->player.x - sin(game->player.rot_angle)
		* (SPRINT(game->player.sprint) + COLLISION_OFFSET);
	y_cpy = game->player.y + cos(game->player.rot_angle)
		* (SPRINT(game->player.sprint) + COLLISION_OFFSET);
	if (!is_a_wall(game, x_cpy, game->player.y))
		game->player.x = game->player.x - sin(game->player.rot_angle)
			* SPRINT(game->player.sprint);
	if (!is_a_wall(game, game->player.x, y_cpy))
		game->player.y = game->player.y + cos(game->player.rot_angle)
			* SPRINT(game->player.sprint);
}

void	move_left(t_game *game)
{
	double	x_cpy;
	double	y_cpy;

	x_cpy = game->player.x + sin(game->player.rot_angle)
		* (SPRINT(game->player.sprint) + COLLISION_OFFSET);
	y_cpy = game->player.y - cos(game->player.rot_angle)
		* (SPRINT(game->player.sprint) + COLLISION_OFFSET);
	if (!is_a_wall(game, x_cpy, game->player.y))
		game->player.x = game->player.x + sin(game->player.rot_angle)
			* SPRINT(game->player.sprint);
	if (!is_a_wall(game, game->player.x, y_cpy))
		game->player.y = game->player.y - cos(game->player.rot_angle)
			* SPRINT(game->player.sprint);
}

void	move_backward(t_game *game)
{
	double	x_cpy;
	double	y_cpy;

	x_cpy = game->player.x - cos(game->player.rot_angle)
		* (SPRINT(game->player.sprint) + COLLISION_OFFSET);
	y_cpy = game->player.y - sin(game->player.rot_angle)
		* (SPRINT(game->player.sprint) + COLLISION_OFFSET);
	if (!is_a_wall(game, x_cpy, game->player.y))
		game->player.x = game->player.x - cos(game->player.rot_angle)
			* SPRINT(game->player.sprint);
	if (!is_a_wall(game, game->player.x, y_cpy))
		game->player.y = game->player.y - sin(game->player.rot_angle)
			* SPRINT(game->player.sprint);
}

void	move_player(t_game *game)
{
	if (game->player.right_rotate)
		game->player.rot_angle += ROTATION_SPEED;
	if (game->player.left_rotate)
		game->player.rot_angle -= ROTATION_SPEED;
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
