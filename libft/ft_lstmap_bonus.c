/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclodic <lclodic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:12:55 by lclodic           #+#    #+#             */
/*   Updated: 2025/11/08 15:10:48 by lclodic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void	ft_lstnew_map(t_list *lst, void *content)
{
	lst->content = content;
	lst->next = NULL;
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;
	t_list	*first;

	if (!lst)
		return (NULL);
	newlist = malloc (sizeof(t_list));
	if (newlist == NULL)
		return (NULL);
	first = newlist;
	while (lst)
	{
		ft_lstnew_map(newlist, f(lst->content));
		if (lst->next)
		{
			newlist->next = malloc (sizeof(t_list));
			if (newlist->next == NULL)
			{
				ft_lstclear(&first, del);
				return (NULL);
			}
			newlist = newlist->next;
		}
		lst = lst->next;
	}
	return (first);
}
