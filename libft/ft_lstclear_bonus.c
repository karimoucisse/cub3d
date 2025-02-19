/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:29:00 by kcisse            #+#    #+#             */
/*   Updated: 2024/05/27 19:26:30 by kcisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*lst_to_del;

	while (*lst)
	{
		(*del)((*lst)->content);
		lst_to_del = *lst;
		*lst = (*lst)->next;
		free(lst_to_del);
	}
}
