/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 10:00:00 by lucas             #+#    #+#             */
/*   Updated: 2026/03/24 10:00:00 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_n_flag(char *s)
{
	int	j;

	if (!s || s[0] != '-' || s[1] != 'n')
		return (0);
	j = 2;
	while (s[j] == 'n')
		j++;
	if (s[j] != '\0')
		return (0);
	return (1);
}

int	ft_echo(char **args)
{
	int	newline;
	int	i;

	newline = 1;
	i = 1;
	while (args[i] && is_n_flag(args[i]))
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
	return (0);
}
