/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:47:10 by kcisse            #+#    #+#             */
/*   Updated: 2025/02/25 01:50:53 by kcisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

int	check_texture(char *str, t_texture *textures)
{
	char	**tab;

	(void)textures;
	tab = ft_split(str, ' ');
	// char *texture_tab;
	if (!tab)
		return (0);
	if (!tab[1])
		return (0);
	if (!ft_strncmp(tab[0], "NO", ft_strlen(tab[0])))
		printf("%s\n", tab[0]);
	if (!ft_strncmp(tab[0], "SO", ft_strlen(tab[0])))
		printf("%s\n", tab[0]);
	if (!ft_strncmp(tab[0], "WE", ft_strlen(tab[0])))
		printf("%s\n", tab[0]);
	if (!ft_strncmp(tab[0], "EA", ft_strlen(tab[0])))
		printf("%s\n", tab[0]);
	if (!ft_strncmp(tab[0], "F", ft_strlen(tab[0])))
		printf("%s\n", tab[0]);
	if (!ft_strncmp(tab[0], "C", ft_strlen(tab[0])))
		printf("%s\n", tab[0]);
	return (1);
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
	if (!textures->no_texture || !textures->so_texture || !textures->we_texture
		|| !textures->ea_texture)
		return (0);
	if (!textures->floor_color->r || !textures->floor_color->g
		|| !textures->floor_color->b)
		return (0);
	if (!textures->ceiling_color->r || !textures->ceiling_color->g
		|| !textures->ceiling_color->b)
		return (0);
	return (1);
}

int	check_map_file(char *map, t_texture *textures)
{
	int		fd;
	char	*line;

	fd = open(map, O_RDONLY);
	line = NULL;
	if (fd == -1)
		printf("Error\n");
	line = get_next_line(fd, 0);
	while (line && !is_check_finished(textures))
	{
		printf("%s\n", line);
		if (!check_texture(line, textures))
			return (free(line), get_next_line(fd, 1), 0);
		free(line);
		line = get_next_line(fd, 0);
	}
	// if(!line || !is_check_finished(textures))
	// si le check de texture n'est pas bon, alors retourner une erreur
	// if (!check_map(map, textures))
	return (0);
}
