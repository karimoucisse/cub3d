/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:47:25 by kcisse            #+#    #+#             */
/*   Updated: 2025/02/25 13:31:10 by kcisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_texture	*init_texture(void)
{
	t_texture	*textures;

	textures = malloc(sizeof(t_texture));
	if (!textures)
		return (0);
	textures->no_texture = NULL;
	textures->so_texture = NULL;
	textures->we_texture = NULL;
	textures->ea_texture = NULL;
	textures->floor_color = malloc(sizeof(t_color));
	textures->ceiling_color = malloc(sizeof(t_color));
	if (!textures->floor_color || !textures->ceiling_color)
		return (0);
	textures->floor_color->r = -1;
	textures->floor_color->g = -1;
	textures->floor_color->b = -1;
	textures->ceiling_color->r = -1;
	textures->ceiling_color->g = -1;
	textures->ceiling_color->b = -1;
	return (textures);
}

int	main(int ac, char **av)
{
	t_texture	*textures;

	textures = NULL;
	if (ac != 2)
		exit(printf("Error\n"));
	textures = init_texture();
	if(!textures)
		exit(printf("Error\n"));
	check_map_file(av[1], textures);
}
