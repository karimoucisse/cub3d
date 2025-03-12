/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:47:25 by kcisse            #+#    #+#             */
/*   Updated: 2025/03/12 09:18:44 by kcisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_game(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Game");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->addr = mlx_get_data_addr(game->img, &game->bits_per_pixel,
			&game->line_length, &game->endian);
	game->player.key_up = False;
	game->player.key_down = False;
	game->player.key_left = False;
	game->player.key_right = False;
	game->player.left_rotate = False;
	game->player.right_rotate = False;
	game->player.x = 6 * 50;
	game->player.y = 7 * 50;
	game->player.angle = PI / 2;
	game->player.pdx = cos(game->player.pa) * 5;
	game->player.pdy = sin(game->player.pa) * 5;
}
int	key_press(int keycode, t_player *player)
{
	// printf("key = %d\n", keycode);
	if (keycode == T)
		player->key_up = true;
	if (keycode == B)
		player->key_down = true;
	if (keycode == L)
		player->key_left = true;
	if (keycode == R)
		player->key_right = true;
	if (keycode == LEFT)
		player->left_rotate = true;
	if (keycode == RIGHT)
		player->right_rotate = true;
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
void	ft_put_pixel(int x, int y, int color, t_game *game)
{
	char	*pxl;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		pxl = game->addr + (y * game->line_length + x * (game->bits_per_pixel
					/ 8));
		*(unsigned int *)pxl = color;
	}
}

char	**get_map(void)
{
	char	**map;

	map = malloc(sizeof(char *) * 11);
	map[0] = "111111111111111";
	map[1] = "100000000000001";
	map[2] = "100000000000001";
	map[3] = "100000100000001";
	map[4] = "100000000000001";
	map[5] = "100000010000001";
	map[6] = "100001000000001";
	map[7] = "100000N00000001";
	map[8] = "100000000000001";
	map[9] = "111111111111111";
	map[10] = NULL;
	return (map);
}

void	draw_square(int x, int y, int size, int color, t_game *game)
{
	for (int i = 0; i < size; i++)
		ft_put_pixel(x + i, y, color, game);
	for (int i = 0; i < size; i++)
		ft_put_pixel(x, y + i, color, game);
	for (int i = 0; i < size; i++)
		ft_put_pixel(x + size, y + i, color, game);
	for (int i = 0; i < size; i++)
		ft_put_pixel(x + i, y + size, color, game);
}

void	clear_image(t_game *game)
{
	for (int y = 0; y < HEIGHT; y++)
		for (int x = 0; x < WIDTH; x++)
			ft_put_pixel(x, y, 0, game);
}
void	move_player(t_player *player)
{
	float	cos_angle;
	float	sin_angle;
	float	angle_speed;
	int		speed;

	speed = 1;
	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	angle_speed = 0.01;
	if (player->left_rotate)
		player->angle -= angle_speed;
	if (player->right_rotate)
		player->angle += angle_speed;
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;
	if (player->key_up)
	{
		player->x += cos_angle * speed;
		player->y += sin_angle * speed;
	}
	if (player->key_down)
	{
		player->x -= cos_angle * speed;
		player->y -= sin_angle * speed;
	}
	if (player->key_left)
	{
		player->x += cos(player->angle + PI / 2) * speed;
		player->y -= sin(player->angle + PI / 2) * speed;
	}
	if (player->key_right)
	{
		player->x -= cos(player->angle + PI / 2) * speed;
		player->y += sin(player->angle + PI / 2) * speed;
	}
}

int	touch(int x, int y, char **map)
{
	int	i;
	int	j;

	i = x / 64;
	j = y / 64;
	if (map[j][i] == '1')
		return (1);
	return (0);
}

int	start_game(t_game *game)
{
	char	**map;
	int		i;
	int		j;
	float	ray_x;
	float	ray_y;
	float	cos_angle;
	float	sin_angle;

	i = 0;
	move_player(&(game->player));
	clear_image(game);
	map = get_map();
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '1')
				draw_square(j * 64, i * 64, 64, 0x00FF00, game);
			if (map[i][j] == 'N')
			{
				printf("x = %f, pdx = %f\n y = %f, pdy = %f\n", game->player.x,
					game->player.pdx, game->player.y, game->player.y);
				draw_square(game->player.x, game->player.y, 32, 0x00FFF0, game);
			}
			j++;
		}
		i++;
	}
	i = 0;
	ray_x = game->player.x;
	ray_y = game->player.y;
	cos_angle = cos(game->player.angle);
	sin_angle = sin(game->player.angle);
	while (!touch(ray_x, ray_y, map))
	{
		ft_put_pixel(ray_x, ray_y, 0x00FF00, game);
		ray_x += cos_angle;
		ray_y += sin_angle;
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

int	main(void)
{
	t_game	game;

	init_game(&game);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game.player);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game.player);
	mlx_loop_hook(game.mlx, start_game, &game);
	mlx_loop(game.mlx);
	return (0);
}

// t_texture	*init_texture(void)
// {
// 	t_texture	*textures;

// 	textures = malloc(sizeof(t_texture));
// 	if (!textures)
// 		return (0);
// 	textures->no_texture = NULL;
// 	textures->so_texture = NULL;
// 	textures->we_texture = NULL;
// 	textures->ea_texture = NULL;
// 	textures->floor_color = malloc(sizeof(t_color));
// 	textures->ceiling_color = malloc(sizeof(t_color));
// 	if (!textures->floor_color || !textures->ceiling_color)
// 		return (0);
// 	textures->floor_color->r = -1;
// 	textures->floor_color->g = -1;
// 	textures->floor_color->b = -1;
// 	textures->ceiling_color->r = -1;
// 	textures->ceiling_color->g = -1;
// 	textures->ceiling_color->b = -1;
// 	return (textures);
// }

// int	main(int ac, char **av)
// {
// 	t_texture	*textures;

// 	textures = NULL;
// 	if (ac != 2)
// 		exit(printf("Error\n"));
// 	textures = init_texture();
// 	if(!textures)
// 		exit(printf("Error\n"));
// 	check_map_file(av[1], textures);
// }
