/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 20:07:15 by kcisse            #+#    #+#             */
/*   Updated: 2024/05/30 14:27:16 by kcisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*lst_copy;
	void	*set;

	if (!lst)
		return (NULL);
	new_lst = NULL;
	while (lst)
	{
		set = f(lst->content);
		lst_copy = ft_lstnew(set);
		if (!lst_copy)
		{
			del(set);
			ft_lstclear(&new_lst, del);
			return (new_lst);
		}
		else
			ft_lstadd_back(&new_lst, lst_copy);
		lst = lst->next;
	}
	return (new_lst);
}
