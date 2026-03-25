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

// if (!args[1]) est là dans le cas où on fait juste cd 
// dans le cas ou on a quelque chose après le cd c'est que c'est le chemin vers lequel on veut aller
static char	*get_cd_path(char **args, char **env)
{
	char	*path;

	if (!args[1])
	{
		path = get_env(env, "HOME");
		if (!path)
			printf("minishell: cd: HOME not set\n");
		return (path);
	}
	return (args[1]);
}

// getcwd est une fonction de la libc, elle malloc direct la string avec le chemin du répertoire courant du processus 
// OLDPWD c'est une variable d'environnement qui est le chemin du directory précédent où on était
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

// chdir change le répertoire courant du processus 
// retourne 0 si ça marche et -1 si erreur 
int	ft_cd(char **args, char ***env)
{
	char	*path;
	char	*oldpwd;

	if (args[1] && args[2])
	{
		printf("minishell: cd: too many arguments\n");
		return (1);
	}
	path = get_cd_path(args, *env);
	if (!path)
		return (1);
	oldpwd = getcwd(NULL, 0);
	if (chdir(path) == -1)
	{
		printf("minishell: cd: %s: No such file or directory\n", path);
		free(oldpwd);
		return (1);
	}
	update_pwd(env, oldpwd);
	free(oldpwd);
	return (0);
}
