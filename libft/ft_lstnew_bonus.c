/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 11:39:28 by kcisse            #+#    #+#             */
/*   Updated: 2024/05/30 12:42:36 by kcisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*first_list;

	first_list = malloc(sizeof(t_list));
	if (first_list == NULL)
		return (0);
	first_list->content = content;
	first_list->next = NULL;
	return (first_list);
}
