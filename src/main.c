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
	// game->player.radius;
	game->player.turn_dir = 0;
	game->player.walk_dir = 0;
	while (game->game_info->map[i])
	{
		j = 0;
		while (game->game_info->map[i][j])
		{
			if (ft_strchr("NWES", game->game_info->map[i][j]))
			{
				game->player.x = j * TILE + TILE / 2;
				game->player.y = i * TILE + TILE / 2;
			}
			if (game->game_info->map[i][j] == 'N')
				game->player.rot_angle = N;
			if (game->game_info->map[i][j] == 'S')
				game->player.rot_angle = S;
			if (game->game_info->map[i][j] == 'E')
				game->player.rot_angle = E;
			if (game->game_info->map[i][j] == 'W')
				game->player.rot_angle = W;
			j++;
		}
		i++;
	}
}

int	start_game(t_game *game)
{
	// raycast_2d(game);
	raycast_3d(game);
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
