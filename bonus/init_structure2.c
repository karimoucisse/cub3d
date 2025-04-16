/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structure2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:27:22 by kcisse            #+#    #+#             */
/*   Updated: 2025/04/16 16:20:27 by kcisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_textures(void *mlx, char *file, t_texture *img)
{
	int	pixel_pos;
	int	y;
	int	x;

	img->img_ptr = mlx_xpm_file_to_image(mlx, file, &img->width, &img->height);
	if (!img->img_ptr)
		return (printf("Error\nFailed mlx_xpm_to_img.\n"), ERROR);
	img->addr = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->line_len,
			&img->endian);
	if (img->width != img->height)
		return (printf("Error\nwidth and height not identique.\n"), ERROR);
	img->pixels = malloc(sizeof(int) * img->width * img->height);
	if (!img->pixels)
		return (printf("Error\nmalloc failed for texture pixels.\n"), ERROR);
	y = -1;
	while (++y < img->height)
	{
		x = -1;
		while (++x < img->width)
		{
			pixel_pos = (y * img->line_len) + (x * (img->bpp / 8));
			img->pixels[y * img->width + x] = *(int *)(img->addr + pixel_pos);
		}
	}
	return (0);
}

int	init_game_loop(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (game->game_info->map[++i])
	{
		j = -1;
		while (game->game_info->map[i][++j])
		{
			if (ft_strchr("NWES", game->game_info->map[i][j]))
			{
				game->player.x = j * TILE + TILE / 2;
				game->player.y = i * TILE + TILE / 2;
			}
			if (game->game_info->map[i][j] == 'N')
				game->player.rot_angle = (3 * PI / 2);
			if (game->game_info->map[i][j] == 'S')
				game->player.rot_angle = PI / 2;
			if (game->game_info->map[i][j] == 'W')
				game->player.rot_angle = PI;
		}
	}
	game->game_info->map_widht = j;
	return (i);
}

int	init_game(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		return (printf("Error\nmlx_init failed\n"), ERROR);
	game->mlx_win = mlx_new_window(game->mlx_ptr, WIDTH, HEIGHT, "Game");
	if (!game->mlx_win)
		return (printf("Error\nmlx_new_window failed\n"), ERROR);
	game->img_ptr = mlx_new_image(game->mlx_ptr, WIDTH, HEIGHT);
	if (!game->img_ptr)
		return (printf("Error\nmlx_new_image failed\n"), ERROR);
	game->addr = mlx_get_data_addr(game->img_ptr, &game->bits_per_pixel,
			&game->line_length, &game->endian);
	game->game_info->map_height = init_game_loop(game);
	if (init_textures(game->mlx_ptr, game->game_info->east_texture,
			&game->ea_data) != SUCCESS || init_textures(game->mlx_ptr,
			game->game_info->north_texture, &game->no_data) != SUCCESS
		|| init_textures(game->mlx_ptr, game->game_info->south_texture,
			&game->so_data) != SUCCESS || init_textures(game->mlx_ptr,
			game->game_info->west_texture, &game->we_data) != SUCCESS
		|| init_textures(game->mlx_ptr, game->game_info->door_texture,
			&game->do_data) != SUCCESS)
		return (ERROR);
	return (SUCCESS);
}
