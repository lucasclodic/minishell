/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 10:00:00 by lucas             #+#    #+#             */
/*   Updated: 2026/03/24 10:00:00 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strncmp(cmd, "echo", 5))
		return (1);
	if (!ft_strncmp(cmd, "cd", 3))
		return (1);
	if (!ft_strncmp(cmd, "pwd", 4))
		return (1);
	if (!ft_strncmp(cmd, "export", 7))
		return (1);
	if (!ft_strncmp(cmd, "unset", 6))
		return (1);
	if (!ft_strncmp(cmd, "env", 4))
		return (1);
	if (!ft_strncmp(cmd, "exit", 5))
		return (1);
	return (0);
}

int	exec_builtin(t_cmd *cmd, char ***env, int last_status)
{
	if (!ft_strncmp(cmd->args[0], "echo", 5))
		return (ft_echo(cmd->args));
	if (!ft_strncmp(cmd->args[0], "cd", 3))
		return (ft_cd(cmd->args, env));
	if (!ft_strncmp(cmd->args[0], "pwd", 4))
		return (ft_pwd());
	if (!ft_strncmp(cmd->args[0], "export", 7))
		return (ft_export(cmd->args, env));
	if (!ft_strncmp(cmd->args[0], "unset", 6))
		return (ft_unset(cmd->args, env));
	if (!ft_strncmp(cmd->args[0], "env", 4))
		return (ft_env(*env));
	if (!ft_strncmp(cmd->args[0], "exit", 5))
		return (ft_exit(cmd->args, last_status));
	return (1);
}
