/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:47:10 by kcisse            #+#    #+#             */
/*   Updated: 2025/04/14 14:38:44 by kcisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_file_name(char *file_name)
{
	int	len;

	len = ft_strlen(file_name);
	if (len < 4)
		return (0);
	if (file_name[len - 1] != 'b' || file_name[len - 2] != 'u')
		return (0);
	if (file_name[len - 3] != 'c' || file_name[len - 4] != '.')
		return (0);
	if (file_name[len - 5] == '/' || file_name[len - 5] == ' ')
		return (0);
	return (1);
}

int	ft_tab_len(char **tab)
{
	int	len;

	len = 0;
	while (tab[len] != 0)
		len++;
	return (len);
}

void	ft_trim(char *line)
{
	int	start;
	int	end;

	start = 0;
	end = ft_strlen(line) - 1;
	while (ft_isspace((unsigned char)line[start]))
		start++;
	while (end > start && ft_isspace((unsigned char)line[end]))
		end--;
	ft_memmove(line, line + start, end - start + 1);
	line[end - start + 1] = '\0';
}

int	file_exist(char *str, char **texture_var)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (close(fd), 0);
	*texture_var = ft_strdup(str);
	if (!texture_var)
		return (0);
	return (1);
}
