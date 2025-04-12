/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcopy_until.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knavarre <knavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 18:51:42 by knavarre          #+#    #+#             */
/*   Updated: 2025/03/23 18:52:44 by knavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcopy_until(char *line, char stop_char)
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
