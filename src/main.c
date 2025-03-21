#include "cub3d.h"

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
			if (ft_strchr("NWES", game->game_info->map[i][j]))
			{
				game->player.x = j * TILE;
				game->player.y = i * TILE;
				j++;
			}
			if(game->game_info->map[i][j] == 'N')
			{
				game->player.dirX = 0;
				game->player.dirY = -1;
				game->player.planeX = 0.66;
				game->player.planeY = 0;
			}
			if(game->game_info->map[i][j] == 'S')
			{
				game->player.dirX = 0;
				game->player.dirY = 1;
				game->player.planeX = -0.66;
				game->player.planeY = 0;
			}
			if(game->game_info->map[i][j] == 'E')
			{
				game->player.dirX = 1;
				game->player.dirY = 0;
				game->player.planeX = 0;
				game->player.planeY = 0.66;
			}
			if(game->game_info->map[i][j] == 'W')
			{
				game->player.dirX = -1;
				game->player.dirY = 0;
				game->player.planeX = 0;
				game->player.planeY = -0.66;
			}
		i++;
	}
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
	// mlx_loop_hook(game.mlx, start_game, &game);
	mlx_loop(game.mlx_ptr);
	return (0);
}
