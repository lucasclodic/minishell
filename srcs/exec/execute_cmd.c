/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnicolas <mnicolas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 09:27:43 by mnicolas          #+#    #+#             */
/*   Updated: 2026/03/31 13:25:35 by mnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_pathh(char **envp, t_cmd *cmds)
{
	int	i;
	char **cmd;

	i = 0;
	cmd = cmds->args;
	if (!envp)
	{
		cmd_not_found(cmd[0]);
		free_cmds(&cmds);
		exit(127);
	}
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	cmd_not_found(cmd[0]);
	free_cmds(&cmds);
	exit(127);
}

char	*get_full_pathh(char **paths, t_cmd *cmds, int i)
{
	char	*tmp;
	char	*full_path;
	char 	**cmd;

	cmd = cmds->args;
	tmp = ft_strjoin(paths[i], "/");
	if (!tmp)
	{
		free_words(paths);
		free_cmds(&cmds);
		exit(1);
	}
	full_path = ft_strjoin(tmp, cmd[0]);
	free(tmp);
	if (!full_path)
	{
		free_words(paths);
		free_cmds(&cmds);
		exit(1);
	}
	return (full_path);
}

char	*search_pathh(char **paths, t_cmd *cmds)
{
	int		i;
	char	*full_path;
	char **cmd;

	i = 0;
	cmd = cmds->args;
	while (paths[i])
	{
		full_path = get_full_pathh(paths, cmds, i);
		if (access(full_path, X_OK) == 0)
		{
			free_words(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	cmd_not_found(cmd[0]);
	free_words(paths);
	free_cmds(&cmds);
	exit(127);
}


void	execc(char *path, t_cmd *cmds, char **envp, int mode)
{
	char **cmd;

	cmd = cmds->args;
	if (execve(path, cmd, envp) == -1)
	{
		if (mode == 1)
			free(path);
		if (errno == ENOENT)
		{
			if (mode == 0)
				perror(cmd[0]);
			else
				cmd_not_found(cmd[0]);
			free_and_exit(cmds, 127);
		}
		if (errno == EACCES)
		{
			perror(cmd[0]);
			free_and_exit(cmds, 126);
		}
		if (mode == 0)
			perror(cmd[0]);
		else
			cmd_not_found(cmd[0]);
		free_and_exit(cmds, 1);
	}
}

void	execute(t_cmd *cmds, char **envp, t_data data)
{
	char	**paths;
	char	*path;
	int 	exit_c;

	free(data.pid);
	if (is_builtin(cmds->args[0]))
	{
		exit_c = exec_builtin(cmds, &envp);
		free_cmds(&cmds);
		exit(exit_c);
	}
	if (ft_strchr(cmds->args[0], '/'))
		execc(cmds->args[0], cmds, envp, 0);
	paths = ft_split(get_pathh(envp, cmds), ':');
	if (!paths)
	{
		free_cmds(&cmds);
		exit (1);
	}
	path = search_pathh(paths, cmds);
	execc(path, cmds, envp, 1);
}
