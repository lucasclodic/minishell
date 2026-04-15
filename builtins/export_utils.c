/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclodic <lclodic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 20:00:00 by lclodic           #+#    #+#             */
/*   Updated: 2026/04/15 20:00:00 by lclodic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_env(char **env)
{
	int	n;

	n = 0;
	while (env[n])
		n++;
	return (n);
}

static char	**copy_env_arr(char **env, int n)
{
	char	**arr;
	int		i;

	arr = malloc(sizeof(char *) * (n + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (i < n)
	{
		arr[i] = env[i];
		i++;
	}
	arr[n] = NULL;
	return (arr);
}

static void	sort_env(char **arr, int n)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < n - 1)
	{
		j = 0;
		while (j < n - 1 - i)
		{
			if (ft_strcmp(arr[j], arr[j + 1]) > 0)
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

char	**sorted_env(char **env)
{
	int		n;
	char	**arr;

	n = count_env(env);
	arr = copy_env_arr(env, n);
	if (!arr)
		return (NULL);
	sort_env(arr, n);
	return (arr);
}
