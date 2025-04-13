/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 13:42:11 by knavarre          #+#    #+#             */
/*   Updated: 2025/04/13 23:36:59 by kcisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int keycode, t_game *game)
{
	if (keycode == T)
		game->player.key_up = true;
	if (keycode == B)
		game->player.key_down = true;
	if (keycode == L)
		game->player.key_left = true;
	if (keycode == R)
		game->player.key_right = true;
	if (keycode == LEFT)
		game->player.left_rotate = true;
	if (keycode == RIGHT)
		game->player.right_rotate = true;
	if (keycode == ECHAP)
		close_win(game);
	return (0);
}

int	key_release(int keycode, t_player *player)
{
	if (keycode == T)
		player->key_up = false;
	if (keycode == B)
		player->key_down = false;
	if (keycode == L)
		player->key_left = false;
	if (keycode == R)
		player->key_right = false;
	if (keycode == LEFT)
		player->left_rotate = false;
	if (keycode == RIGHT)
		player->right_rotate = false;
	return (0);
}

void	move_forward(t_game *game)
{
	double	x_cpy;
	double	y_cpy;

	x_cpy = game->player.x + cos(game->player.rot_angle) * (MOVE_SPEED + COLLISION_OFFSET);
	y_cpy = game->player.y + sin(game->player.rot_angle) * (MOVE_SPEED + COLLISION_OFFSET);
	if (!is_a_wall(game, x_cpy, game->player.y))
		game->player.x = game->player.x + cos(game->player.rot_angle) * MOVE_SPEED;
	if (!is_a_wall(game, game->player.x, y_cpy))
		game->player.y = game->player.y + sin(game->player.rot_angle) * MOVE_SPEED;
}

void	move_right(t_game *game)
{
	double	x_cpy;
	double	y_cpy;

	x_cpy = game->player.x - sin(game->player.rot_angle) * (MOVE_SPEED + COLLISION_OFFSET);
	y_cpy = game->player.y + cos(game->player.rot_angle) * (MOVE_SPEED + COLLISION_OFFSET);
	if (!is_a_wall(game, x_cpy, game->player.y))
		game->player.x = game->player.x - sin(game->player.rot_angle) * MOVE_SPEED;
	if (!is_a_wall(game, game->player.x, y_cpy))
		game->player.y = game->player.y + cos(game->player.rot_angle) * MOVE_SPEED;
}

void	move_left(t_game *game)
{
	double	x_cpy;
	double	y_cpy;

	x_cpy = game->player.x + sin(game->player.rot_angle) * (MOVE_SPEED + COLLISION_OFFSET);
	y_cpy = game->player.y - cos(game->player.rot_angle) * (MOVE_SPEED + COLLISION_OFFSET);
	if (!is_a_wall(game, x_cpy, game->player.y))
		game->player.x = game->player.x + sin(game->player.rot_angle) * MOVE_SPEED;
	if (!is_a_wall(game, game->player.x, y_cpy))
		game->player.y = game->player.y - cos(game->player.rot_angle) * MOVE_SPEED;
}

void	move_backward(t_game *game)
{
	double	x_cpy;
	double	y_cpy;

	x_cpy = game->player.x - cos(game->player.rot_angle) * (MOVE_SPEED + COLLISION_OFFSET);
	y_cpy = game->player.y - sin(game->player.rot_angle) * (MOVE_SPEED + COLLISION_OFFSET);
	if (!is_a_wall(game, x_cpy, game->player.y))
		game->player.x = game->player.x - cos(game->player.rot_angle) * MOVE_SPEED;
	if (!is_a_wall(game, game->player.x, y_cpy))
		game->player.y = game->player.y - sin(game->player.rot_angle) * MOVE_SPEED;
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
