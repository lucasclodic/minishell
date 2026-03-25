/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 10:00:00 by lucas             #+#    #+#             */
/*   Updated: 2026/03/24 10:00:00 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// unset VAR1 VAR2 ... → supprime chaque variable de env
// si la variable n'existe pas, on ignore silencieusement
int	ft_unset(char **args, char ***env)
{
	int	i;

	i = 1;
	while (args[i])
	{
		remove_env(env, args[i]);
		i++;
	}
	return (0);
}
