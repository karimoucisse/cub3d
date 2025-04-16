/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_action.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knavarre <knavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:53:18 by kcisse            #+#    #+#             */
/*   Updated: 2025/04/15 23:21:09 by knavarre         ###   ########.fr       */
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
	if (keycode == CTRL)
		game->player.sprint = true;
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
	if (keycode == CTRL)
		player->sprint = false;
	return (0);
}

int	mouse_move(int x, int y, t_game *game)
{
	int			center_x;
	int			center_y;
	int			delta_x;
	double		sensitivity;
	(void)y;

	center_x = WIDTH / 2;
	center_y = HEIGHT / 2;
	sensitivity = 0.001;
	delta_x = x - center_x;
	game->player.rot_angle += delta_x * sensitivity;
	mlx_mouse_move(game->mlx_ptr, game->mlx_win, center_x, center_y);
	return (0);
}
