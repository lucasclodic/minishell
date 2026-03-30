/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclodic <lclodic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 10:10:22 by lclodic           #+#    #+#             */
/*   Updated: 2025/11/12 10:31:57 by lclodic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*test;

	if (new == NULL)
		return ;
	if (!(*lst))
	{
		(*lst) = new;
		return ;
	}
	test = *(lst);
	while (test && test->next)
		test = test->next;
	test->next = new;
}

// int main()
// {
// 	t_list *a;
// 	t_list *b;
// 	t_list *c;

// 	a = malloc(sizeof(t_list));
// 	b = malloc(sizeof(t_list));
// 	c = malloc(sizeof(t_list));

// 	a->content = "Premier";
// 	a->next = b;

// 	b->content = "Second";
// 	b->next = c;

// 	c->content = "Dernier";
// 	c->next = NULL;

// 	t_list **head = NULL;

// 	t_list *add;
// 	add = malloc(sizeof(t_list));
// 	add->content = "Nouveau";
// 	add->next = NULL;

// 	ft_lstadd_back(head, add);

// 	// while ((*head))
// 	// {
// 	// 	printf("%s\n", (char *)(*head)->content);
// 	// 	(*head) = (*head)->next;
// 	// }
// }
