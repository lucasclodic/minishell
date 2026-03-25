/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get-env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 17:57:16 by lucas             #+#    #+#             */
/*   Updated: 2026/03/24 12:04:07 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env(char **env, char *name)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(name);
	if (!env)
		return (NULL);
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

char	**copy_env(char **envp)
{
	int		i;
	char	**output;

	i = 0;
	while (envp[i])
		i++;
	output = malloc(sizeof(char *) * (i + 1));
	if (!output)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		output[i] = ft_strdup(envp[i]);
		if (!output[i])
		{
			free_args(output, i);
			return (NULL);
		}
		i++;
	}
	output[i] = NULL;
	return (output);
}
