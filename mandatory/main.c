/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knavarre <knavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:02:23 by knavarre          #+#    #+#             */
/*   Updated: 2025/04/13 21:44:44 by knavarre         ###   ########.fr       */
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
		return (printf("Error: width and height not identique.\n"), ERROR);
	img->pixels = malloc(sizeof(int) * img->width * img->height);
	if (!img->pixels)
		return (printf("Error: malloc failed for texture pixels.\n"), ERROR);
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

int	init_game(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		return (printf("Error: mlx_init failed\n"), ERROR);
	game->mlx_win = mlx_new_window(game->mlx_ptr, WIDTH, HEIGHT, "Game");
	if (!game->mlx_win)
		return (printf("Error: mlx_new_window failed\n"), ERROR);
	game->img_ptr = mlx_new_image(game->mlx_ptr, WIDTH, HEIGHT);
	if (!game->img_ptr)
		return (printf("Error: mlx_new_image failed\n"), ERROR);
	game->addr = mlx_get_data_addr(game->img_ptr, &game->bits_per_pixel,
			&game->line_length, &game->endian);
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
	game->game_info->map_height = i;
	init_textures(game->mlx_ptr, game->game_info->east_texture,
		&game->EA_data);
	init_textures(game->mlx_ptr, game->game_info->north_texture,
		&game->NO_data);
	init_textures(game->mlx_ptr, game->game_info->south_texture,
		&game->SO_data);
	init_textures(game->mlx_ptr, game->game_info->west_texture,
		&game->WE_data);
	return (SUCCESS);
}

int	start_game(t_game *game)
{
	raycast_3d(game);
	return (0);
}

void free_list(t_list *lst)
{
	t_list	*tmp;

	if (!lst)
		return ;
	while (lst != NULL)
	{
		tmp = lst->next;
		if (lst->content != NULL)
			free(lst->content);
		free(lst);
		lst = NULL;
		lst = tmp;
	}
}

void	free_map(char **map)
{
	int i;

	i = 0;
	if (!map)
		return ;
	while(map[i])
	{
		ft_free(&map[i]);
		i++;
	}
	free(map);
}

void	free_structure(t_game *game)
{
	if (game->game_info)
	{
		ft_free(&game->game_info->north_texture);
		ft_free(&game->game_info->east_texture);
		ft_free(&game->game_info->south_texture);
		ft_free(&game->game_info->west_texture);
		free_list(game->game_info->map_list);
		free_map(game->game_info->map);
		free(game->game_info);
	}
}

int	close_win(t_game *game)
{
	if (!game)
		exit(1);
	if (game->mlx_ptr)
	{
		if (game->img_ptr)
			mlx_destroy_image(game->mlx_ptr, game->img_ptr);
		if (game->NO_data.img_ptr)
			mlx_destroy_image(game->mlx_ptr, game->NO_data.img_ptr);
		if (game->SO_data.img_ptr)
			mlx_destroy_image(game->mlx_ptr, game->SO_data.img_ptr);
		if (game->WE_data.img_ptr)
			mlx_destroy_image(game->mlx_ptr, game->WE_data.img_ptr);
		if (game->EA_data.img_ptr)
			mlx_destroy_image(game->mlx_ptr, game->EA_data.img_ptr);
		if (game->mlx_win)
			mlx_destroy_window(game->mlx_ptr, game->mlx_win);
		if (game->EA_data.pixels)
			free(game->EA_data.pixels);
		if (game->SO_data.pixels)
			free(game->SO_data.pixels);
		if (game->WE_data.pixels)
			free(game->WE_data.pixels);
		if (game->NO_data.pixels)
			free(game->NO_data.pixels);
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
	free_structure(game);
	exit(0);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		return (EXIT_FAILURE);
	if (!check_file_name(av[1]))
		printf("Error\n");
	if (init_structure(&game) != SUCCESS)
		return (ERROR);
	if (opening_parsing(game.game_info, av[1]) != SUCCESS)
		return (free_structure(&game), ERROR);

	if (init_game(&game) != SUCCESS)
		return (free_structure(&game), ERROR);
		
	mlx_hook(game.mlx_win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.mlx_win, 3, 1L << 1, key_release, &game.player);
	mlx_hook(game.mlx_win, 17, 0, close_win, &game);
	mlx_loop_hook(game.mlx_ptr, start_game, &game);
	mlx_loop(game.mlx_ptr);
	return (0);
}
