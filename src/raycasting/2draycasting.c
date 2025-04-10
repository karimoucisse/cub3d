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
				draw_square(j * MINIMAP_TILE, i * MINIMAP_TILE, 0,
					MINIMAP_TILE, game);
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
	double	new_x;
	double	new_y;
	double	step;

	i = 0;
	new_x = game->player.x / TILE * MINIMAP_TILE;
	new_y = game->player.y / TILE * MINIMAP_TILE;
	// x = (new_x + 5) + cos(angle) * i;
	// y = (new_y + 5) + sin(angle) * i;
	while (1)
	{
		x = (new_x) + cos(angle) * i;
		y = (new_y) + sin(angle) * i;
		// if (x >= game->raycast_info.wall_hitx
		// 	|| y >= game->raycast_info.wall_hity)
		// break ;
		// if (is_a_wall(game->game_info->map, x - 0.2, y - 0.2)
		// 	|| is_a_wall(game->game_info->map, x + 0.2, y + 0.2))
		// 	break ;
		if (is_a_wall(game->game_info->map, x / MINIMAP_TILE * TILE, y
				/ MINIMAP_TILE * TILE))
			break ;
		i++;
		ft_put_pixel(x, y, 0xFFFFF0, game);
	}
}

void	raycast_2d(t_game *game)
{
	int		i;
	double	angle;
	double	x;
	double	y;

	create_map(game);
	x = game->player.x / TILE * MINIMAP_TILE;
	y = game->player.y / TILE * MINIMAP_TILE;
	draw_square(x, y, 0, 2, game);
	i = 0;
	angle = game->player.rot_angle - (FOV / 2);
	while (i < WIDTH)
	{
		draw_ray(game, angle);
		angle += FOV / WIDTH;
		i++;
	}
}
