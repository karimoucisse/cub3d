/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixels.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:12:23 by kcisse            #+#    #+#             */
/*   Updated: 2025/04/14 15:13:15 by kcisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

double	put_ceiling_pixel(t_game *game, int x)
{
	int		y;
	double	wall_top_pixel;
	int		color;

	wall_top_pixel = (HEIGHT / 2) - (game->raycast_info.wall_height / 2);
	if (wall_top_pixel < 0)
		wall_top_pixel = 0;
	y = 0;
	while (y < wall_top_pixel)
	{
		color = rgb_to_int(game->game_info->ceiling_color[0],
				game->game_info->ceiling_color[1],
				game->game_info->ceiling_color[2]);
		ft_put_pixel(x, y, color, game);
		y++;
	}
	return (wall_top_pixel);
}

double	put_floor_pixel(t_game *game, int x)
{
	int		y;
	double	wall_bottom_pixel;
	int		color;

	wall_bottom_pixel = (HEIGHT / 2) + (game->raycast_info.wall_height / 2);
	if (wall_bottom_pixel > HEIGHT)
		wall_bottom_pixel = HEIGHT;
	y = wall_bottom_pixel;
	while (y < HEIGHT)
	{
		color = rgb_to_int(game->game_info->floor_color[0],
				game->game_info->floor_color[1],
				game->game_info->floor_color[2]);
		ft_put_pixel(x, y, color, game);
		y++;
	}
	return (wall_bottom_pixel);
}

void	put_wall_pixel(t_game *game, t_texture texture, int y, int x)
{
	int	distance_from_top;
	int	color;
	int	texture_offset_x;
	int	texture_offset_y;

	texture_offset_x = get_xcord(game);
	distance_from_top = y + (game->raycast_info.wall_height / 2) - (HEIGHT / 2);
	texture_offset_y = distance_from_top * ((float)texture.height
			/ game->raycast_info.wall_height);
	color = texture.pixels[(texture.width * texture_offset_y)
		+ texture_offset_x];
	ft_put_pixel(x, y, color, game);
}
