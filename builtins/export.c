/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 10:00:00 by lucas             #+#    #+#             */
/*   Updated: 2026/03/24 10:00:00 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// verifie que le nom de variable est valide
// doit commencer par une lettre ou _ puis que des alphanumeriques ou _
static int	is_valid_name(char *name, int len)
{
	int	i;

	if (len == 0 || !(name[0] == '_' || (name[0] >= 'a' && name[0] <= 'z')
			|| (name[0] >= 'A' && name[0] <= 'Z')))
		return (0);
	i = 1;
	while (i < len)
	{
		if (!(name[i] == '_' || (name[i] >= 'a' && name[i] <= 'z')
				|| (name[i] >= 'A' && name[i] <= 'Z')
				|| (name[i] >= '0' && name[i] <= '9')))
			return (0);
		i++;
	}
	return (1);
}

// "export" sans argument -> affiche toutes les variables au format :
// declare -> NAME="value"
// attention à bien tester en bash et pas zsh, bash -c "export | head -3" affiche le declare -x
static void	print_export(char **env)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		ft_putstr_fd("declare -x ", 1);
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			write(1, &env[i][j++], 1);
		if (env[i][j] == '=')
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(env[i] + j + 1, 1);
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		i++;
	}
}

// "export VAR=value" -> ajoute ou modifie la variable dans env
// "export VAR" sans = -> ne fait rien
// retourne 1 si erreur sur au moins un argument
static int	find_eq(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	if (arg[i] != '=')
		return (-1);
	if (!is_valid_name(arg, i))
	{
		print_error("export", arg, "not a valid identifier");
		return (-2);
	}
	return (i);
}

static int	handle_export_arg(char *arg, char ***env)
{
	int		eq_pos;
	char	*name;
	char	*value;

	eq_pos = find_eq(arg); // position du =
	if (eq_pos == -1)
	{
		if (!is_valid_name(arg, ft_strlen(arg)))
		{
			print_error("export", arg, "not a valid identifier");
			return (1);
		}
		return (0);
	}
	if (eq_pos == -2)
		return (1);
	name = ft_substr(arg, 0, eq_pos);
	value = ft_strdup(arg + eq_pos + 1);
	if (!name || !value)
	{
		free(name);
		free(value);
		return (1);
	}
	set_env(env, name, value);
	free(name);
	free(value);
	return (0);
}

int	ft_export(char **args, char ***env)
{
	int	i;
	int	ret;

	if (!args[1])
	{
		print_export(*env);
		return (0);
	}
	ret = 0;
	i = 1;
	while (args[i])
	{
		if (handle_export_arg(args[i], env))
			ret = 1;
		i++;
	}
	return (ret);
}
