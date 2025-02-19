/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:47:10 by kcisse            #+#    #+#             */
/*   Updated: 2025/02/19 11:47:11 by kcisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_texture(char *str, t_texture *textures)
{
	// split str
	// si le tableau split est > a 2
	// retourner une erreur
	// verifier si tab[0] est egale a NO, SO, WE, EA
	// verifier si tab[1] est un fichier qui peut etre ouvert.
	// sinon verifier si tab[0] est egale a F ou C
	// verifier si tab[1] comprend 3 nombre entre 0 et 255.
}

int	is_check_finished(t_texture *textures)
{
	t_color	*floor_color;
	t_color	*ceiling_color;

	floor_color = textures->floor_color;
	ceiling_color = textures->ceiling_color;
	if (!textures->no_texture || !textures->so_texture || !textures->we_texture
		|| !textures->ea_texture)
		return (0);
	if (!floor_color->r || !floor_color->g || !floor_color->b)
		return (0);
	if (!ceiling_color->r || !ceiling_color->g || !ceiling_color->b)
		return (0);
	return (1);
}

int	check_map_file(char *map, t_texture *textures)
{
	int		fd;
	char	*line;

	fd = open(map, O_RDONLY);
	if (fd == -1)
		write(1, "Error\n", 6);
	while (get_next_line(fd, &line) > 0 && !is_check_finished(textures))
	{
		if (!check_texture(line, textures))
			return (free(line), 0);
	}
	if (!check_map(map, textures))
		return (0);
}
