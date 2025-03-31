#include "cub3d.h"

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

void	draw_ray(t_game *game, double angle)
{
	int		i;
	double	x;
	double	y;

	i = 0;
	x = (game->player.x + 5) + cos(angle) * i;
	y = (game->player.y + 5) + sin(angle) * i;
	while (1)
	{
		x = (game->player.x) + cos(angle) * i;
		y = (game->player.y) + sin(angle) * i;
		if (is_a_wall(game->game_info->map, x - 0.2, y - 0.2)
			|| is_a_wall(game->game_info->map, x + 0.2, y + 0.2))
			break ;
		if (is_a_wall(game->game_info->map, x, y))
			break ;
		i++;
		ft_put_pixel(x, y, 0x00FFF0, game);
	}
}

void	raycast_2d(t_game *game)
{
	int		i;
	double	angle;

	move_player(game);
	create_map(game);
	draw_square(game->player.x, game->player.y, 0x00FFF0, 10, game);
	i = 0;
	angle = game->player.rot_angle - (FOV / 2);
	while (i < WIDTH)
	{
		// intersections(game, normalize_angle(angle));
		draw_ray(game, angle);
		angle += FOV / WIDTH;
		i++;
	}
	mlx_put_image_to_window(game->mlx_ptr, game->mlx_win, game->img_ptr, 0, 0);
}
