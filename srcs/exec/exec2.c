/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclodic <lclodic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 17:45:00 by lclodic           #+#    #+#             */
/*   Updated: 2026/04/15 17:45:00 by lclodic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_open_err(t_data *data, t_cmd **cmd)
{
	if (data->open_code == 130)
	{
		close_in_out(data->infd, data->outfd);
		return (free_pid_return(130, data->pid));
	}
	if (data->cmd_count == 1)
	{
		close_in_out(data->infd, data->outfd);
		return (free_pid_return(1, data->pid));
	}
	if (data->outfd > 2)
		close(data->outfd);
	if (data->i < data->cmd_count - 1 && create_pipe(data) == -1)
	{
		if (data->infd > 2)
			close(data->infd);
		return (free_pid_return(1, data->pid));
	}
	next_command(data, cmd);
	return (-1);
}

int	dispatch_cmd(t_cmd *cmd, char ***envp, t_data *data)
{
	if (!cmd->args[0] && data->cmd_count == 1)
	{
		close_in_out(data->infd, data->outfd);
		return (free_pid_return(0, data->pid));
	}
	if (cmd->args[0] && data->cmd_count == 1 && is_builtin(cmd->args[0]))
	{
		free(data->pid);
		return (execute_builtin(cmd, envp, *data));
	}
	if (cmd->args[0] && fork_child(cmd, data, *envp) == -1)
	{
		close_in_out(data->infd, data->outfd);
		if (data->i > 0)
			return (wait_and_return(*data));
		return (free_pid_return(1, data->pid));
	}
	return (-1);
}
