#include "cub3d.h"

int	is_a_wall(char **map, double x, double y)
{
	int	x_block;
	int	y_block;

	x_block = floor(x / TILE);
	y_block = floor(y / TILE);
	if (!map[y_block] || !map[y_block][x_block] || (map[y_block][x_block] != '1'
			&& map[y_block][x_block] != ' '))
		return (0);
	return (1);
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

// void	draw_square(int x, int y, int color, int size, t_game *game)
// {
// 	int	i;

// 	i = 0;
// 	while (i < size)
// 	{
// 		ft_put_pixel(x + i, y, color, game);
// 		ft_put_pixel(x + i, y + size, color, game);
// 		ft_put_pixel(x, y + i, color, game);
// 		ft_put_pixel(x + size, y + i, color, game);
// 		i++;
// 	}
// }
// void	create_map(t_game *game)
// {
// 	int		i;
// 	int		j;
// 	char	**map;
// 	int tile = WIDTH / 4 / 27;
// 	double x;
// 	double y;

// 	i = 0;
// 	map = game->game_info->map;
// 	while (map[i])
// 	{
// 		j = 0;
// 		while (map[i][j])
// 		{
// 			if (map[i][j] == '1')
// 				draw_square(j * tile, i * tile, 0x00FF00, tile, game);
// 			j++;
// 		}
// 		i++;
// 	}
// 	x = (game->player.x / 64) * 8;
// 	y = (game->player.y / 64) * 8;
// 	draw_square(x, y, 0x00FFF0, 2, game);
// }

// void	mini_map(t_game *game)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < HEIGHT / 4)
// 	{
// 		j = 0;
// 		while (j < WIDTH  / 4)
// 		{
// 			ft_put_pixel(j, i, 0, game);
// 			j++;
// 		}
// 		i++;
// 	}
// 	create_map(game);
// }
