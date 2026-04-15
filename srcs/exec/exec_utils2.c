/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnicolas <mnicolas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 14:25:12 by mnicolas          #+#    #+#             */
/*   Updated: 2026/04/01 14:24:16 by mnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0')
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	get_lines(char *delim, t_data *data)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (g_signal == SIGINT)
		{
			g_signal = 0;
			free(line);
			close(data->pipefd[0]);
			close(data->pipefd[1]);
			return (130);
		}
		if (!line || ft_strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		write(data->pipefd[1], line, strlen(line));
		write(data->pipefd[1], "\n", 1);
		free(line);
	}
	close(data->pipefd[1]);
	return (0);
}

int	count_cmds(t_cmd *cmds)
{
	int		i;
	t_cmd	*tmp;

	tmp = cmds;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

int	wait_and_return(t_data data)
{
	int	i;
	int	status;
	int	exit_code;

	i = 0;
	exit_code = 0;
	while (i < data.cmd_count)
	{
		if (data.pid[i] != -1)
		{
			waitpid(data.pid[i], &status, 0);
			if (i == data.cmd_count - 1)
				exit_code = compute_exit_status(status);
		}
		else if (i == data.cmd_count - 1)
			exit_code = 1;
		if (i == data.cmd_count - 1)
			setup_signals_interactive();
		i++;
	}
	free(data.pid);
	return (exit_code);
}

void	execve_err_msg(char *cmd, int mode)
{
	if (mode == 0)
		shell_perror(cmd);
	else
		cmd_not_found(cmd);
}
