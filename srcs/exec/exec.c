/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 18:35:05 by mnicolas          #+#    #+#             */
/*   Updated: 2026/04/07 19:38:56 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	work_child(t_cmd *cmd, char **envp, t_data data)
{
	if (dup2(data.infd, 0) == -1 || dup2(data.outfd, 1) == -1)
	{
		if (data.infd > 2)
			close(data.infd);
		if (data.outfd > 2)
			close(data.outfd);
		free_cmds(&cmd);
		free_perror_exit("dup2", data);
	}
	if (data.infd > 2)
		close(data.infd);
	if (data.outfd > 2)
		close(data.outfd);
	if (data.pipefd[0] > 2 && data.pipefd[0] != data.infd)
		close(data.pipefd[0]);
	execute(cmd, envp, data);
}

int	fork_child(t_cmd *cmd, t_data *data, char **envp)
{
	data->pid[data->i] = fork();
	if (data->pid[data->i] == -1)
	{
		perror("fork");
		return (-1);
	}
	if (data->pid[data->i] == 0)
	{
		setup_signals_default();
		work_child(cmd, envp, *data);
	}
	return (0);
}

int	execute_builtin(t_cmd *cmd, char **envp, t_data data)
{
	int	exit_c;
	int	stdin_backup;
	int	stdout_backup;

	setup_signals_interactive();
	stdin_backup = dup(0);
	stdout_backup = dup(1);
	if (stdin_backup == -1 || stdout_backup == -1)
		close_backup_and_return(stdin_backup, stdout_backup, "dup");
	if (dup2(data.infd, 0) == -1 || (dup2(data.outfd, 1) == -1))
	{
		close_in_out(data.infd, data.outfd);
		close_backup_and_return(stdin_backup, stdout_backup, "dup2");
	}
	exit_c = exec_builtin(cmd, &envp);
	dup2(stdin_backup, 0);
	dup2(stdout_backup, 1);
	close(stdin_backup);
	close(stdout_backup);
	if (g_signal == SIGINT)
	{
		g_signal = 0;
		return (130);
	}
	return (exit_c);
}

void next_command(t_data *data, t_cmd **cmd)
{
	close_in_out(data->infd, data->outfd);
	data->i++;
	*cmd = (*cmd)->next;
}

int	exec(t_cmd *cmd, char **envp)
{
	t_data	data;

	data.data_code = init_data(&data, cmd);
	if (data.data_code != 0)
		return (data.data_code);
	while (cmd)
	{
		setup_signals_ignore();
		data.open_code = open_redirs(cmd->redirs, &data);
		if (data.open_code != 0)
		{
			if (data.open_code == 130)
				return (free_pid_return(130, data.pid));
			if (data.cmd_count == 1)
				return (free_pid_return(1, data.pid));
			if (data.outfd > 2)
				close(data.outfd);
			if (data.i < data.cmd_count - 1
				&& create_pipe(NULL, &data) == -1)
				return (free_pid_return(1, data.pid));
			next_command(&data, &cmd);
			continue ;
		}
		if (!cmd->args[0] && data.cmd_count == 1)
		{
			close_in_out(data.infd, data.outfd);
			return (free_pid_return(0, data.pid));
		}
		if (cmd->args[0] && data.cmd_count == 1 && is_builtin(cmd->args[0]))
		{
			free(data.pid);
			return (execute_builtin(cmd, envp, data));
		}
		if (cmd->args[0] && fork_child(cmd, &data, envp) == -1)
			return (free_pid_return(1, data.pid));
		next_command(&data, &cmd);
	}
	return (wait_and_return(data));
}
