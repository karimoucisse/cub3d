#include "cub3d.h"

void	init_game(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	game->mlx_ptr = mlx_init();
	game->mlx_win = mlx_new_window(game->mlx_ptr, WIDTH, HEIGHT, "Game");
	game->img_ptr = mlx_new_image(game->mlx_ptr, WIDTH, HEIGHT);
	game->addr = mlx_get_data_addr(game->img_ptr, &game->bits_per_pixel,
			&game->line_length, &game->endian);
	game->player.key_up = False;
	game->player.key_down = False;
	game->player.key_left = False;
	game->player.key_right = False;
	game->player.left_rotate = False;
	game->player.right_rotate = False;
	while (game->game_info->map[i])
	{
		j = 0;
		while (game->game_info->map[i][j])
		{
			if (ft_strchr("NWES", game->game_info->map[i][j]))
			{
				game->player.x = j * TILE;
				game->player.y = i * TILE;
			}
			if (game->game_info->map[i][j] == 'N')
			{
				game->player.dirX = 0;
				game->player.dirY = -1;
				game->player.planeX = 0.66;
				game->player.planeY = 0;
			}
			if (game->game_info->map[i][j] == 'S')
			{
				game->player.dirX = 0;
				game->player.dirY = 1;
				game->player.planeX = -0.66;
				game->player.planeY = 0;
			}
			if (game->game_info->map[i][j] == 'E')
			{
				game->player.dirX = 1;
				game->player.dirY = 0;
				game->player.planeX = 0;
				game->player.planeY = 0.66;
			}
			if (game->game_info->map[i][j] == 'W')
			{
				game->player.dirX = -1;
				game->player.dirY = 0;
				game->player.planeX = 0;
				game->player.planeY = -0.66;
			}
			j++;
		}
		i++;
	}
}
int	key_press(int keycode, t_player *player)
{
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

void	draw_square(int x, int y, int color, int size, t_game *game)
{
	int	i;

	i = 0;
	while (i < size)
	{
		ft_put_pixel(x + i, y, color, game);
		ft_put_pixel(x + i, y + size, color, game);
		ft_put_pixel(x, y + i, color, game);
		ft_put_pixel(x + size, y + i, color, game);
		i++;
	}
}
void	create_map(t_game *game)
{
	int		i;
	int		j;
	char	**map;

	i = 0;
	map = game->game_info->map;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '1')
				draw_square(j * TILE, i * TILE, 0x00FF00, TILE, game);
			j++;
		}
		i++;
	}
}

void	move_player(t_game *game)
{
	double	mv_speed;
	char	**map;
	double	angle_speed;
	double	old_planeX;
	double	old_dirX;

	angle_speed = 0.005;
	map = game->game_info->map;
	mv_speed = 0.4;
	if (game->player.key_up)
	{
		game->player.x += game->player.dirX * mv_speed;
		game->player.y += game->player.dirY * mv_speed;
	}
	if (game->player.key_down)
	{
		game->player.x -= game->player.dirX * mv_speed;
		game->player.y -= game->player.dirY * mv_speed;
	}
	if (game->player.key_left)
	{
		game->player.x -= game->player.planeX * mv_speed;
		game->player.y -= game->player.planeY * mv_speed;
	}
	if (game->player.key_right)
	{
		game->player.x += game->player.planeX * mv_speed;
		game->player.y += game->player.planeY * mv_speed;
	}
	if (game->player.left_rotate)
	{
		old_planeX = game->player.planeX;
		old_dirX = game->player.dirX;
		game->player.dirX = game->player.dirX * cos(angle_speed)
			- game->player.dirY * sin(angle_speed);
		game->player.dirY = old_dirX * sin(angle_speed) + game->player.dirY
			* cos(angle_speed);
		game->player.planeX = game->player.planeX * cos(angle_speed)
			- game->player.planeY * sin(angle_speed);
		game->player.planeY = old_planeX * sin(angle_speed)
			+ game->player.planeY * cos(angle_speed);
	}
	if (game->player.right_rotate)
	{
		old_planeX = game->player.planeX;
		old_dirX = game->player.dirX;
		game->player.dirX = game->player.dirX * cos(-angle_speed)
			- game->player.dirY * sin(-angle_speed);
		game->player.dirY = old_dirX * sin(-angle_speed) + game->player.dirY
			* cos(-angle_speed);
		game->player.planeX = game->player.planeX * cos(-angle_speed)
			- game->player.planeY * sin(-angle_speed);
		game->player.planeY = old_planeX * sin(-angle_speed)
			+ game->player.planeY * cos(-angle_speed);
	}
}

void	clear_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			ft_put_pixel(j, i, 0, game);
			j++;
		}
		i++;
	}
}

void	raycast_2d(t_game *game)
{
	int		i;
	double	x;
	double	y;
	double	px;
	double	py;

	move_player(game);
	clear_map(game);
	create_map(game);
	draw_square(game->player.x + TILE / 2, game->player.y + TILE / 2, 0x00FFF0,
		10, game);
	i = 0;
	px = game->player.planeX;
	py = game->player.planeY;
	while (i < 40)
	{
		x = ((game->player.x + TILE/2 + (px * i)));
		y = ((game->player.y + TILE/2 + (py * i)));
		i++;
		ft_put_pixel(x, y, 0x00FFF0, game);
	}
	mlx_put_image_to_window(game->mlx_ptr, game->mlx_win, game->img_ptr, 0, 0);
}

int	start_game(t_game *game)
{
	raycast_2d(game);
	return (0);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		return (EXIT_FAILURE);
	if (!check_file_name(av[1]))
		printf("Error\n");
	game.game_info = parse_file(av[1]);
	init_game(&game);
	mlx_hook(game.mlx_win, 2, 1L << 0, key_press, &game.player);
	mlx_hook(game.mlx_win, 3, 1L << 1, key_release, &game.player);
	mlx_loop_hook(game.mlx_ptr, start_game, &game);
	mlx_loop(game.mlx_ptr);
	return (0);
}
