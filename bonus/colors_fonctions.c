/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_fonctions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knavarre <knavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 13:23:21 by knavarre          #+#    #+#             */
/*   Updated: 2025/04/12 13:24:41 by knavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	colors_verifing(char *str)
{
	int	i;
	int	value;

	i = 0;
	if (!str || *str == '\0')
		return (ERROR);
	while (str[i] && str[i] != ' ' && str[i] != '\t')
	{
		if (!ft_isdigit(str[i]))
		{
			printf("RGB color is no good\n");
			return (ERROR);
		}
		i++;
	}
	value = ft_atoi(str);
	if (value < 0 || value > 255)
	{
		printf("Error : the color value is not between 0 y 255\n");
		return (ERROR);
	}
	return (SUCCESS);
}

int	colors_function(int (*tab)[3], char *line)
{
	char	*temp_number;
	int		i;
	int		start;

	start = 0;
	i = 0;
	temp_number = NULL;
	if ((*tab)[0] != -1)
		return (printf("colors duplicates\n"), ERROR);
	while (start < 3)
	{
		while (line[i] && (line[i] == ' ' || line[i] == '\t'))
			i++;
		temp_number = ft_strcopy_until(line + i, ',');
		if (!temp_number)
			return (ERROR);
		if (colors_verifing(temp_number) != SUCCESS)
			return (ft_free(&temp_number), ERROR);
		(*tab)[start++] = ft_atoi(temp_number);
		i += ft_strlen(temp_number) + 1;
		ft_free(&temp_number);
	}
	return (ft_free(&temp_number), SUCCESS);
}
