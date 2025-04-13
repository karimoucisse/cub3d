/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_fonctions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knavarre <knavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 13:16:21 by knavarre          #+#    #+#             */
/*   Updated: 2025/04/13 21:22:19 by knavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_textures(char **line)
{
	int			fd;
	char		*file;
	const char	*prefix;

	prefix = "includes/textures";
	file = malloc(ft_strlen(prefix) + ft_strlen(*line + 1) + 1);
	if (!file)
		return (ERROR);
	ft_strcpy(file, prefix);
	ft_strcat(file, *line + 1);
	if (!file)
		return (ERROR);
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_free(&file);
		return (ERROR);
	}
	ft_free(line);
	*line = file;
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
		printf("new_line = %s\n", new_line);
		if (ft_strlen(new_line) >= 4
			&& ft_strncmp(new_line + ft_strlen(new_line) - 4, ".xpm", 4) != 0)
		{
			*file = new_line;
			return (printf("not xpm file.\n"), ERROR);
		}
		if (is_valid_textures(&new_line) != SUCCESS)
		{
			printf("Error : unable to open the texture [%s].\n", line);
			return (ft_free(&new_line), ERROR);
		}
		*file = new_line;
		return (SUCCESS);
	}
	printf("Error : %s duplicates\n", *file);
	return (ERROR);
}
