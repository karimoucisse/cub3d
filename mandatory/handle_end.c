/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_end.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knavarre <knavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:27:13 by kcisse            #+#    #+#             */
/*   Updated: 2025/04/15 23:22:39 by knavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_list(t_list *lst)
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
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
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
		ft_free(&game->game_info->door_texture);
		free_list(game->game_info->map_list);
		free_map(game->game_info->map);
		free(game->game_info);
	}
}

void	ft_destroy_image(t_game *game)
{
	if (game->img_ptr)
		mlx_destroy_image(game->mlx_ptr, game->img_ptr);
	if (game->no_data.img_ptr)
		mlx_destroy_image(game->mlx_ptr, game->no_data.img_ptr);
	if (game->so_data.img_ptr)
		mlx_destroy_image(game->mlx_ptr, game->so_data.img_ptr);
	if (game->we_data.img_ptr)
		mlx_destroy_image(game->mlx_ptr, game->we_data.img_ptr);
	if (game->ea_data.img_ptr)
		mlx_destroy_image(game->mlx_ptr, game->ea_data.img_ptr);
	if (game->do_data.img_ptr)
		mlx_destroy_image(game->mlx_ptr, game->do_data.img_ptr);
}

int	close_win(t_game *game)
{
	if (!game)
		exit(1);
	if (game->mlx_ptr)
	{
		ft_destroy_image(game);
		if (game->mlx_win)
			mlx_destroy_window(game->mlx_ptr, game->mlx_win);
		if (game->ea_data.pixels)
			free(game->ea_data.pixels);
		if (game->so_data.pixels)
			free(game->so_data.pixels);
		if (game->we_data.pixels)
			free(game->we_data.pixels);
		if (game->no_data.pixels)
			free(game->no_data.pixels);
		if (game->do_data.pixels)
			free(game->do_data.pixels);
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
	free_structure(game);
	exit(0);
}
