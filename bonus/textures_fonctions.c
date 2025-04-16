/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_fonctions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 13:16:21 by knavarre          #+#    #+#             */
/*   Updated: 2025/04/16 12:54:01 by kcisse           ###   ########.fr       */
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
		if (ft_strlen(new_line) >= 4
			&& ft_strncmp(new_line + ft_strlen(new_line) - 4, ".xpm", 4) != 0)
		{
			*file = new_line;
			return (print_error("not xpm file.\n"));
		}
		if (is_valid_textures(&new_line) != SUCCESS)
		{
			printf("Error\nError : unable to open the texture [%s].", line);
			return (ft_free(&new_line), ERROR);
		}
		*file = new_line;
		return (SUCCESS);
	}
	printf("Error\nError : %s duplicates\n", *file);
	return (ERROR);
}
