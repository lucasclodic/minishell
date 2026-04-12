/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnicolas <mnicolas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 15:08:34 by mnicolas          #+#    #+#             */
/*   Updated: 2026/04/01 15:44:08 by mnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	free_pid_return(int code, pid_t *pid)
{
	free(pid);
	return (code);
}

int	open_and_error(t_data *data, t_cmd *cmd)
{
	data->open_code = open_redirs(cmd->redirs, data);
	if (data->open_code == -1)
	{
		if (data->cmd_count == 1)
		{
			close_in_out(data->infd, data->outfd);
			return (free_pid_return(1, data->pid));
		}
		if (data->infd > 2)
			close(data->infd);
		data->infd = open("/dev/null", O_RDONLY);
		if (data->infd == -1)
			return (free_pid_return(1, data->pid));
		return (0);
	}
	else if (data->open_code == 130)
	{
		close_in_out(data->infd, data->outfd);
		return (free_pid_return(130, data->pid));
	}
	return (0);
}

int	init_data(t_data *data, t_cmd *cmd)
{
	int	i;

	data->i = 0;
	data->infd = -2;
	data->here_doc = 0;
	data->cmd_count = count_cmds(cmd);
	data->pid = malloc(data->cmd_count * sizeof(pid_t));
	if (!data->pid)
	{
		perror("malloc");
		return (1);
	}
	i = -1;
	while (++i < data->cmd_count)
		data->pid[i] = -1;
	return (0);
}

void	close_backup_and_return(int stdin_backup, int stdout_backup, char *str)
{
	close(stdin_backup);
	close(stdout_backup);
	free_perror_return(str);
}

void	close_in_out(int infd, int outfd)
{
	if (infd > 2)
		close(infd);
	if (outfd > 2)
		close(outfd);
}
