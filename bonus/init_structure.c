/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structure.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knavarre <knavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 13:26:28 by knavarre          #+#    #+#             */
/*   Updated: 2025/04/16 13:04:33 by knavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_player(t_player *player)
{
	if (!player)
		return (ERROR);
	player->x = 0;
	player->y = 0;
	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	player->left_rotate = false;
	player->right_rotate = false;
	player->radius = 0;
	player->rot_angle = 0;
	player->turn_dir = 0;
	player->walk_dir = 0;
	player->sprint = false;
	return (SUCCESS);
}

int	init_info(t_game_info *info)
{
	int	i;

	i = 0;
	if (!info)
	{
		printf("Error\ninfo not initialized\n.");
		return (ERROR);
	}
	info->north_texture = NULL;
	info->south_texture = NULL;
	info->west_texture = NULL;
	info->east_texture = NULL;
	info->door_texture = NULL;
	while (i < 3)
	{
		info->floor_color[i] = -1;
		info->ceiling_color[i] = -1;
		i++;
	}
	info->map = NULL;
	info->map_list = NULL;
	info->lock = 0;
	info->lock_valid_map_lines = 0;
	info->lock_news = 0;
	return (SUCCESS);
}

int	init_raycast(t_raycast *raycast)
{
	if (!raycast)
		return (ERROR);
	raycast->was_hit_vertical = false;
	raycast->v_hit_posx = 0;
	raycast->v_hit_posy = 0;
	raycast->v_hit_dist = 0;
	raycast->h_hit_posx = 0;
	raycast->h_hit_posy = 0;
	raycast->h_hit_dist = 0;
	raycast->wall_hitx = 0;
	raycast->wall_hity = 0;
	raycast->wall_hit_dist = 0;
	raycast->wall_height = 0;
	raycast->color = 0;
	return (SUCCESS);
}

int	init_texture(t_texture *tex)
{
	if (!tex)
		return (ERROR);
	tex->img_ptr = NULL;
	tex->addr = NULL;
	tex->width = 0;
	tex->height = 0;
	tex->bpp = 0;
	tex->line_len = 0;
	tex->endian = 0;
	tex->pixels = NULL;
	return (SUCCESS);
}

int	init_structure(t_game *data)
{
	if (!data)
		return (printf("Error\ndata not initialized.\n"), ERROR);
	data->mlx_ptr = NULL;
	data->mlx_win = NULL;
	data->img_ptr = NULL;
	data->addr = NULL;
	data->bits_per_pixel = 0;
	data->line_length = 0;
	data->endian = 0;
	data->game_info = malloc(sizeof(t_game_info));
	if (!data->game_info)
		return (printf("Error\nmalloc failed for game_info.\n"), ERROR);
	if (init_info(data->game_info) != SUCCESS)
		return (ERROR);
	if (init_player(&data->player) != SUCCESS)
		return (ERROR);
	if (init_raycast(&data->raycast_info) != SUCCESS)
		return (ERROR);
	if (init_texture(&data->no_data) != SUCCESS
		|| init_texture(&data->so_data) != SUCCESS
		|| init_texture(&data->ea_data) != SUCCESS
		|| init_texture(&data->we_data) != SUCCESS
		|| init_texture(&data->do_data) != SUCCESS)
		return (ERROR);
	return (SUCCESS);
}
