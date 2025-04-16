/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_fonctions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 13:16:21 by knavarre          #+#    #+#             */
/*   Updated: 2025/04/16 16:00:59 by kcisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_textures(char **line)
{
	int	fd;

	fd = open(*line, O_RDONLY);
	if (fd == -1)
		return (ERROR);
	close(fd);
	return (SUCCESS);
}

int	textures_function(char **file, char *line, int i)
{
	char	*new_line;

	new_line = NULL;
	if (*file == NULL)
	{
		new_line = ft_strcopy_until(line + i + 2, ' ');
		if (!new_line)
			return (ERROR);
		if (ft_strlen(new_line) >= 4 && ft_strncmp(new_line
				+ ft_strlen(new_line) - 4, ".xpm", 4) != 0)
		{
			*file = new_line;
			return (printf("Error\nnot xpm file.\n"), ERROR);
		}
		if (is_valid_textures(&new_line) != SUCCESS)
		{
			printf("Error\nunable to open the texture [%s].\n", line);
			return (ft_free(&new_line), ERROR);
		}
		*file = new_line;
		return (SUCCESS);
	}
	printf("Error\n%s duplicates\n", *file);
	return (ERROR);
}
