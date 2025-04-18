/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_fonctions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knavarre <knavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 13:23:21 by knavarre          #+#    #+#             */
/*   Updated: 2025/04/18 13:16:13 by knavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strlen_color(char *str)
{
	int		i;
	int		len;
	bool	after_space;

	i = 0;
	len = 0;
	after_space = false;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			after_space = true;
		if ((after_space && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			|| (!ft_strchr("0123456789 \t", str[i])))
		{
			len = -1;
			break ;
		}
		if (!after_space)
			len++;
		i++;
	}
	if (str[0] == '0' && len > 1)
		return (-1);
	return (len);
}

char	*ft_strcopy_until_t(char *line, char stop_char)
{
	char	*new_str;
	int		i;
	int		len;
	int		start;

	i = 0;
	len = 0;
	start = 0;
	if (!line)
		return (NULL);
	while (line[start] && (line[start] == ' ' || line[start] == '\t'))
		start++;
	while (line[start + len] && line[start + len] != stop_char
		&& line[start + len] != '\n')
		len++;
	new_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (NULL);
	len += start;
	while (start < len)
		new_str[i++] = line[start++];
	new_str[i] = '\0';
	return (new_str);
}

int	colors_verifing(char *str)
{
	int	i;
	int	value;

	i = 0;
	if (!str || *str == '\0' || ft_strlen_color(str) > 3
		|| ft_strlen_color(str) < 1)
		return (printf("Error\nRGB color is no good\n"), ERROR);
	while (str[i] && str[i] != ' ' && str[i] != '\t')
	{
		if (!ft_isdigit(str[i]))
		{
			printf("Error\nRGB color is no good\n");
			return (ERROR);
		}
		i++;
	}
	value = ft_atoi(str);
	if (value < 0 || value > 255)
	{
		printf("Error\nthe color value is not between 0 y 255\n");
		return (ERROR);
	}
	return (SUCCESS);
}

int	count_virgule(char *line)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == ',')
			count++;
		i++;
	}
	return (count);
}

int	colors_function(int (*tab)[3], char *line)
{
	char	*temp_number;
	int		i;
	int		start;

	start = 0;
	i = 0;
	temp_number = NULL;
	if (count_virgule(line) != 2)
		return (printf("Error\ninvalid colors\n"), ERROR);
	if ((*tab)[0] != -1)
		return (printf("Error\ncolors duplicates\n"), ERROR);
	while (start < 3)
	{
		while (line[i] && (line[i] == ' ' || line[i] == '\t'))
			i++;
		temp_number = ft_strcopy_until_t(line + i, ',');
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
