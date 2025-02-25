/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:47:25 by kcisse            #+#    #+#             */
/*   Updated: 2025/02/25 01:41:44 by kcisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_texture(t_texture *textures)
{
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
	return (1);
}

int	main(int ac, char **av)
{
	t_texture	*textures;
	textures = NULL;
	if (ac != 2)
		exit(printf("Error\n"));
	if (!init_texture(textures))
		exit(printf("Error\n"));
	check_map_file(av[1], textures);
}
