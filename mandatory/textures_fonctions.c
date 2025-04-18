/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_fonctions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knavarre <knavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 13:16:21 by knavarre          #+#    #+#             */
/*   Updated: 2025/04/18 13:07:47 by knavarre         ###   ########.fr       */
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

int	textures_function2(int pos, char *new_line, char *line)
{
	pos += ft_strlen(new_line);
	while (line[pos] && (line[pos] == ' ' || line[pos] == '\t'))
		pos++;
	if (line[pos] != '\0' && line[pos] != '\n')
		return (printf("Error\nTexture.\n"), ERROR);
	if (ft_strlen(new_line) >= 4 && ft_strncmp(new_line
			+ ft_strlen(new_line) - 4, ".xpm", 4) != 0)
		return (printf("Error\nnot xpm.\n"), ERROR);
	return (SUCCESS);
}

int	textures_function(char **file, char *line, int i)
{
	char	*new_line;
	int		pos;

	new_line = NULL;
	pos = i + 2;
	if (line[pos] && line[pos] != ' ' && line[pos] != '\t')
		return (printf("Error\n"), ERROR);
	if (*file == NULL)
	{
		while (line[pos] && (line[pos] == ' ' || line[pos] == '\t'))
			pos++;
		new_line = ft_strcopy_until(line + i + 2, ' ');
		if (!new_line)
			return (ERROR);
		if (textures_function2(pos, new_line, line) != SUCCESS)
			return (ft_free(&new_line), ERROR);
		if (is_valid_textures(&new_line) != SUCCESS)
		{
			printf("Error\nunable to open the texture [%s].\n", line);
			return (ft_free(&new_line), ERROR);
		}
		*file = new_line;
		return (SUCCESS);
	}
	return (printf("Error\n%s duplicates\n", *file), ERROR);
}
