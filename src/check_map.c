/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:47:10 by kcisse            #+#    #+#             */
/*   Updated: 2025/02/25 18:09:54 by kcisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

int	ft_tab_len(char **tab)
{
	int	len;

	len = 0;
	while (tab[len] != 0)
		len++;
	return (len);
}
int	verify_colors(t_color *color_val, char **tab)
{
	int		tab_len;
	char	**tab_color;
	int		i;

	tab_len = ft_tab_len(tab);
	if (tab_len == 2)
	{
		i = 0;
		while (tab[1][i])
		{
			if (!ft_strchr("1234567890,", tab[1][i]))
				return (0);
			i++;
		}
		tab_color = ft_split(tab[1], ',');
		if (ft_tab_len(tab_color) > 3)
			return (0);
		color_val->r = ft_atoi(tab_color[0]);
		color_val->g = ft_atoi(tab_color[1]);
		color_val->b = ft_atoi(tab_color[2]);
	}
	printf("r = %d, g = %d, b = %d\n", color_val->r, color_val->g, color_val->b);
	// if(tab_len == 4)
	// {
	// 	// si tab0123 ne contient pas une valeur differente de '1234567890,
			// ' et que
	// 	// sans ', ' tab0123 a une valeur =< 3
	// }
	return (0);
}
int	verify_texture_path(char *texture_path, char **tab)
{
	int	tab_len;
	int	fd;

	// char	*path;
	tab_len = ft_tab_len(tab);
	if (tab_len != 2)
		return (0);
	// path = ft_substr(tab[1], 0, ft_strlen(tab[1]) - 1);
	fd = open(tab[1], O_RDONLY);
	if (fd == -1)
		return (0);
	texture_path = tab[1];
	printf("%s\n", texture_path);
	close(fd);
	return (1);
}
int	check_texture(char *str, t_texture *textures)
{
	char	**tab;
	char	*line;

	(void)textures;
	if (ft_strlen(str) < 2)
		return (1);
	line = ft_substr(str, 0, ft_strlen(str) - 1);
	tab = ft_split(line, ' ');
	if (!tab)
		return (0);
	if (!tab[1])
		return (0);
	if (!ft_strncmp(tab[0], "NO", ft_strlen(tab[0])))
		verify_texture_path(textures->no_texture, tab);
	else if (!ft_strncmp(tab[0], "SO", ft_strlen(tab[0])))
		verify_texture_path(textures->so_texture, tab);
	else if (!ft_strncmp(tab[0], "WE", ft_strlen(tab[0])))
		verify_texture_path(textures->we_texture, tab);
	else if (!ft_strncmp(tab[0], "EA", ft_strlen(tab[0])))
		verify_texture_path(textures->ea_texture, tab);
	else if (!ft_strncmp(tab[0], "F", ft_strlen(tab[0])))
		verify_colors(textures->floor_color, tab);
	else if (!ft_strncmp(tab[0], "C", ft_strlen(tab[0])))
		verify_colors(textures->ceiling_color, tab);
	else if (ft_strchr(str, ' ') || ft_strchr(str, '\n'))
		return (1);
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
	if (textures->floor_color->r == -1 || textures->floor_color->g == -1
		|| textures->floor_color->b == -1)
		return (0);
	if (textures->ceiling_color->r == -1 || textures->ceiling_color->g == -1
		|| textures->ceiling_color->b == -1)
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
