/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclodic <lclodic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 09:35:24 by lclodic           #+#    #+#             */
/*   Updated: 2025/11/06 09:57:40 by lclodic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void *content)
{
	t_list	*output;

	output = malloc(sizeof(t_list));
	if (output == NULL)
		return (NULL);
	output->content = content;
	output->next = NULL;
	return (output);
}
