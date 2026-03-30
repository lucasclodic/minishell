/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnicolas <mnicolas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 09:27:43 by mnicolas          #+#    #+#             */
/*   Updated: 2026/03/30 13:53:11 by mnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_pathh(char **envp, t_cmd *cmds)
{
	int	i;
	char **cmd;

	i = 0;
	cmd = cmds->args;
	while (envp[i])
	{
		if (strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	cmd_not_found(cmd[0]);
	freee_cmds(cmds);
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
		freee_cmds(cmds);
		exit(1);
	}
	full_path = ft_strjoin(tmp, cmd[0]);
	free(tmp);
	if (!full_path)
	{
		free_words(paths);
		freee_cmds(cmds);
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
	freee_cmds(cmds);
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

char	*fttt_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if ((const unsigned char)s[i] == (const unsigned char)c)
			return ((char *)(s + i));
		i++;
	}
	if ((const unsigned char)s[i] == (unsigned char)c)
		return ((char *)(s + i));
	return (NULL);
}

void	execute(t_cmd *cmds, char **envp, t_data data)
{
	char	**paths;
	char	*path;

	free(data.pid);
	if (fttt_strchr(cmds->args[0], '/'))
		execc(cmds->args[0], cmds, envp, 0);
	paths = ft_split(get_pathh(envp, cmds), ':');
	if (!paths)
	{
		freee_cmds(cmds);
		exit (1);
	}
	path = search_pathh(paths, cmds);
	execc(path, cmds, envp, 1);
}
