/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set-env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 12:00:00 by lucas             #+#    #+#             */
/*   Updated: 2026/03/24 12:00:00 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*join_env(char *name, char *value)
{
	char	*entry;
	int		len_n;
	int		len_v;
	int		i;

	len_n = ft_strlen(name);
	len_v = ft_strlen(value);
	entry = malloc(len_n + 1 + len_v + 1);
	if (!entry)
		return (NULL);
	i = -1;
	while (name[++i])
		entry[i] = name[i];
	entry[i++] = '=';
	len_v = 0;
	while (value[len_v])
		entry[i++] = value[len_v++];
	entry[i] = '\0';
	return (entry);
}

static int	add_env(char ***env, char *entry)
{
	char	**new_env;
	int		i;

	i = 0;
	while ((*env)[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (free(entry), 0);
	i = -1;
	while ((*env)[++i])
		new_env[i] = (*env)[i];
	new_env[i] = entry;
	new_env[i + 1] = NULL;
	free(*env);
	*env = new_env;
	return (1);
}

int	set_env(char ***env, char *name, char *value)
{
	int		i;
	int		len;
	char	*entry;

	entry = join_env(name, value);
	if (!entry)
		return (0);
	len = ft_strlen(name);
	i = 0;
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], name, len) == 0 && (*env)[i][len] == '=')
		{
			free((*env)[i]);
			(*env)[i] = entry;
			return (1);
		}
		i++;
	}
	return (add_env(env, entry));
}

void	remove_env(char ***env, char *name)
{
	int	i;
	int	j;
	int	len;

	len = ft_strlen(name);
	i = 0;
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], name, len) == 0 && (*env)[i][len] == '=')
		{
			free((*env)[i]);
			j = i;
			while ((*env)[j + 1])
			{
				(*env)[j] = (*env)[j + 1];
				j++;
			}
			(*env)[j] = NULL;
			return ;
		}
		i++;
	}
}
