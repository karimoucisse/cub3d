/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:47:10 by kcisse            #+#    #+#             */
/*   Updated: 2025/03/21 12:21:09 by kcisse           ###   ########.fr       */
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

void	init_game_info(t_game_info *info)
{
	info->x = -1;
	info->y = -1;
	info->north_texture = NULL;
	info->south_texture = NULL;
	info->west_texture = NULL;
	info->east_texture = NULL;
	info->map = NULL;
	info->floor_color[0] = -1;
	info->floor_color[1] = -1;
	info->floor_color[2] = -1;
	info->ceiling_color[0] = -1;
	info->ceiling_color[1] = -1;
	info->ceiling_color[2] = -1;
}

t_game_info	*parse_file(char *file)
{
	int			fd;
	char		*line;
	t_game_info	*game_info;

	fd = open(file, O_RDONLY);
	game_info = malloc(sizeof(t_game_info));
	if (fd == -1)
		return (0);
	line = NULL;
	line = get_next_line(fd, 0);
	if (!line)
		return (0);
	init_game_info(game_info);
	while (line && !check_texture(game_info))
	{
		ft_trim(line);
		if ((int)ft_strlen(line) != 0)
		{
			if (!parse_texture(line, game_info))
				return (0);
		}
		free(line);
		line = get_next_line(fd, 0);
	}
	int i = 0;
	game_info->map = parse_map(fd, line);
	while(game_info->map[i])
	{
		printf("%s\n", game_info->map[i]);
		i++;
	}
	return (0);
}
