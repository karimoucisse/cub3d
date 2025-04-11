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

t_texture	get_texture(t_game *game, double angle)
{
	if (game->raycast_info.v_hit_dist > game->raycast_info.h_hit_dist)
	// Si l'intersection horizontale est la plus proche
	{
		if (sin(angle) > 0)
			return (game->NO_data);
		else
			return (game->SO_data);
	}
	else // Sinon, l'intersection verticale est la plus proche
	{
		if (cos(angle) > 0)
			return(game->WE_data);
		else
			return(game->EA_data);
	}
}
