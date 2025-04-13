/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knavarre <knavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:57:39 by kcisse            #+#    #+#             */
/*   Updated: 2025/04/13 19:03:59 by knavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// duplicate a string
char	*ft_strdup(const char *str)
{
	int		i;
	char	*dup;

	i = 0;
	if (!str)
		return (NULL);
	dup = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (dup == NULL)
		return (0);
	while (str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
