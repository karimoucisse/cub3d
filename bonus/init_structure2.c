/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structure2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:27:22 by kcisse            #+#    #+#             */
/*   Updated: 2025/04/16 11:19:35 by kcisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_textures(void *mlx, char *file, t_texture *img)
{
	int	pixel_pos;
	int	y;
	int	x;

	y = 0;
	img->img_ptr = mlx_xpm_file_to_image(mlx, file, &img->width, &img->height);
	img->addr = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->line_len,
			&img->endian);
	if (img->width != img->height)
		return (print_error("Error: width and height not identique.\n"));
	img->pixels = malloc(sizeof(int) * img->width * img->height);
	if (!img->pixels)
		return (print_error("Error: malloc failed for texture pixels.\n"));
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			pixel_pos = (y * img->line_len) + (x * (img->bpp / 8));
			img->pixels[y * img->width + x] = *(int *)(img->addr + pixel_pos);
			x++;
		}
		y++;
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
			if (game->game_info->map[i][j] == 'E')
				game->player.rot_angle = 0;
			if (game->game_info->map[i][j] == 'W')
				game->player.rot_angle = PI;
		}
	}
	return (i);
}

int	init_game(t_game *game)
{
	int	i;

	i = 0;
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		return (print_error("Error: mlx_init failed\n"));
	game->mlx_win = mlx_new_window(game->mlx_ptr, WIDTH, HEIGHT, "Game");
	if (!game->mlx_win)
		return (print_error("Error: mlx_new_window failed\n"));
	game->img_ptr = mlx_new_image(game->mlx_ptr, WIDTH, HEIGHT);
	if (!game->img_ptr)
		return (print_error("Error: mlx_new_image failed\n"));
	game->addr = mlx_get_data_addr(game->img_ptr, &game->bits_per_pixel,
			&game->line_length, &game->endian);
	i = init_game_loop(game);
	game->game_info->map_height = i;
	init_textures(game->mlx_ptr, game->game_info->east_texture, &game->ea_data);
	init_textures(game->mlx_ptr, game->game_info->north_texture,
		&game->no_data);
	init_textures(game->mlx_ptr, game->game_info->south_texture,
		&game->so_data);
	init_textures(game->mlx_ptr, game->game_info->west_texture, &game->we_data);
	return (SUCCESS);
}
