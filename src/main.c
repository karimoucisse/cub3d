#include "cub3d.h"

int	init_textures(void *mlx, char *file, t_texture *img)
{
	int	pixel_pos;

	img->img_ptr = mlx_xpm_file_to_image(mlx, file, &img->width, &img->height);
	img->addr = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->line_len,
			&img->endian);
	img->pixels = malloc(sizeof(int) * img->width * img->height);
	if (!img->pixels)
		return (printf("Error: malloc failed for texture pixels.\n"), 1);
	// Récupérer les pixels de l'image
	for (int y = 0; y < img->height; y++)
	{
		for (int x = 0; x < img->width; x++)
		{
			pixel_pos = (y * img->line_len) + (x * (img->bpp / 8));
			img->pixels[y * img->width + x] = *(int *)(img->addr + pixel_pos);
		}
	}
	return (1);
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
	game->NO_data.img_ptr = NULL;
	game->NO_data.addr = NULL;
	game->SO_data.img_ptr = NULL;
	game->SO_data.addr = NULL;
	game->WE_data.img_ptr = NULL;
	game->WE_data.addr = NULL;
	game->EA_data.img_ptr = NULL;
	game->EA_data.addr = NULL;
	init_textures(game->mlx_ptr, "./textures/wolfenstein/blue_stone.xpm",
		&game->EA_data);
	init_textures(game->mlx_ptr, "./textures/wolfenstein/wood.xpm",
		&game->NO_data);
	init_textures(game->mlx_ptr, "./textures/wolfenstein/color_stone.xpm",
		&game->SO_data);
	init_textures(game->mlx_ptr, "./textures/wolfenstein/grey_stone.xpm",
		&game->WE_data);
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
