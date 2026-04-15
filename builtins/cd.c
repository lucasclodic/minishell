/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 10:00:00 by lucas             #+#    #+#             */
/*   Updated: 2026/03/24 10:00:00 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <sys/stat.h>

static char	*get_cd_path(char **args, char **env)
{
	char	*path;

	if (!args[1])
	{
		path = get_env(env, "HOME");
		if (!path)
			print_error("cd", NULL, "HOME not set");
		return (path);
	}
	return (args[1]);
}

static void	update_pwd(char ***env, char *oldpwd)
{
	char	*newpwd;

	set_env(env, "OLDPWD", oldpwd);
	newpwd = getcwd(NULL, 0);
	if (newpwd)
	{
		set_env(env, "PWD", newpwd);
		free(newpwd);
	}
}

static void	cd_error(char *path)
{
	if (errno == ENOTDIR)
		print_error("cd", path, "Not a directory");
	else if (errno == EACCES)
		print_error("cd", path, "Permission denied");
	else
		print_error("cd", path, "No such file or directory");
}

int	ft_cd(char **args, char ***env)
{
	char	*path;
	char	*oldpwd;

	if (args[1] && args[2])
	{
		print_error("cd", NULL, "too many arguments");
		return (1);
	}
	path = get_cd_path(args, *env);
	if (!path)
		return (1);
	oldpwd = getcwd(NULL, 0);
	if (chdir(path) == -1)
	{
		cd_error(path);
		free(oldpwd);
		return (1);
	}
	update_pwd(env, oldpwd);
	free(oldpwd);
	return (0);
}
