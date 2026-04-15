/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclodic <lclodic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 09:27:43 by mnicolas          #+#    #+#             */
/*   Updated: 2026/04/15 17:09:01 by lclodic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_pathh(char **envp, t_cmd *cmds, t_data data)
{
	int		i;
	char	**cmd;

	i = 0;
	cmd = cmds->args;
	if (!envp)
	{
		cmd_not_found(cmd[0]);
		child_cleanup_and_exit(cmds, envp, data, 127);
	}
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	cmd_not_found(cmd[0]);
	child_cleanup_and_exit(cmds, envp, data, 127);
	return (NULL);
}

char	*get_full_pathh(char **paths, t_cmd *cmds, int i)
{
	char	*tmp;
	char	*full_path;

	tmp = ft_strjoin(paths[i], "/");
	if (!tmp)
		return (NULL);
	full_path = ft_strjoin(tmp, cmds->args[0]);
	free(tmp);
	return (full_path);
}

char	*search_pathh(char **paths, t_cmd *cmds, char **envp, t_data data)
{
	int		i;
	char	*full_path;

	i = 0;
	while (paths[i])
	{
		full_path = get_full_pathh(paths, cmds, i);
		if (!full_path)
		{
			free_words(paths);
			child_cleanup_and_exit(cmds, envp, data, 1);
		}
		if (access(full_path, X_OK) == 0)
		{
			free_words(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	cmd_not_found(cmds->args[0]);
	free_words(paths);
	child_cleanup_and_exit(cmds, envp, data, 127);
	return (NULL);
}

void	execc(char *path, t_cmd *cmds, char **envp, t_data data)
{
	char	**cmd;

	cmd = cmds->args;
	if (execve(path, cmd, envp) == -1)
	{
		if (data.exec_mode == 1)
			free(path);
		if (errno == ENOENT)
		{
			execve_err_msg(cmd[0], data.exec_mode);
			child_cleanup_and_exit(cmds, envp, data, 127);
		}
		if (errno == EACCES)
		{
			shell_perror(cmd[0]);
			child_cleanup_and_exit(cmds, envp, data, 126);
		}
		execve_err_msg(cmd[0], data.exec_mode);
		child_cleanup_and_exit(cmds, envp, data, 1);
	}
}

void	execute(t_cmd *cmds, char **envp, t_data data)
{
	char	**paths;
	char	*path;
	int		exit_c;

	free(data.pid);
	data.pid = NULL;
	if (is_builtin(cmds->args[0]))
	{
		exit_c = exec_builtin(cmds, &envp);
		child_cleanup_and_exit(cmds, envp, data, exit_c);
	}
	if (ft_strchr(cmds->args[0], '/'))
	{
		data.exec_mode = 0;
		execc(cmds->args[0], cmds, envp, data);
	}
	paths = ft_split(get_pathh(envp, cmds, data), ':');
	if (!paths)
		child_cleanup_and_exit(cmds, envp, data, 1);
	path = search_pathh(paths, cmds, envp, data);
	data.exec_mode = 1;
	execc(path, cmds, envp, data);
}
