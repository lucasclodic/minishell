/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 17:08:51 by lucas             #+#    #+#             */
/*   Updated: 2026/03/19 17:08:52 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(char *str)
{
	char	*dup;
	int		len;
	int		i;

	len = ft_strlen(str);
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_substr(char *str, int start, int end)
{
	char *output; 
	int i; 

	output = malloc(sizeof(char) * (end - start + 1));
	if (!output)
		return (NULL);
	i = 0; 
	while (str[start] && start < end)
	{
		output[i] = str[start]; 
		start++; 
		i++; 
	}
	output[i] = '\0';
	return (output);
}