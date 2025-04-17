/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_fonctions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knavarre <knavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 13:16:21 by knavarre          #+#    #+#             */
/*   Updated: 2025/04/17 11:49:56 by knavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_textures(char **line)
{
	int			fd;

	fd = open(*line, O_RDONLY);
	if (fd == -1)
		return (ERROR);
	close(fd);
	return (SUCCESS);
}

int	textures_function(char **file, char *line, int i)
{
	char	**new_line;

	new_line = NULL;
	if (*file == NULL)
	{
		new_line = ft_split(line + i + 2, ' ');
		printf("newline0 = %s\nnewline1 = %s\n", new_line[0], new_line[1]);
		if (!new_line || new_line[1])
			return (free_map(new_line), ERROR);
		if (ft_strlen(new_line[0]) >= 4
			&& ft_strncmp(new_line[0] + (ft_strlen(new_line[0])) - 4, ".xpm", 4) != 0)
		{
			printf("line = %s", new_line[0] + (ft_strlen(new_line[0])) - 4 );
			printf("strncmp = %d\n", ft_strncmp(new_line[0] + ft_strlen(new_line[0]) - 4, ".xpm", 4));
			printf("newline0 = %s\nstrlen= %zu\n", new_line[0], ft_strlen(new_line[0]));
			free_map(new_line);
			return (printf("Error\nnot xpm file.\n"), ERROR);
		}
		if (is_valid_textures(&new_line[0]) != SUCCESS)
		{
			printf("Error\nunable to open the texture [%s].\n", line);
			return (free_map(new_line), ERROR);
		}
		*file = new_line[0];
		return (SUCCESS);
	}
	printf("Error\n%s duplicates\n", *file);
	return (ERROR);
}
