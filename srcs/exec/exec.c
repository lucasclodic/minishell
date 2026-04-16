/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclodic <lclodic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 18:35:05 by mnicolas          #+#    #+#             */
/*   Updated: 2026/04/15 16:49:52 by lclodic          ###   ########.fr       */
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
		shell_perror("dup2");
		child_cleanup_and_exit(cmd, envp, data, 1);
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
		shell_perror("fork");
		return (-1);
	}
	if (data->pid[data->i] == 0)
	{
		setup_signals_default();
		work_child(cmd, envp, *data);
	}
	return (0);
}

int	execute_builtin(t_cmd *cmd, char ***envp, t_data data)
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
	exit_c = exec_builtin(cmd, envp, data.exit_status);
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

void	next_command(t_data *data, t_cmd **cmd)
{
	close_in_out(data->infd, data->outfd);
	data->i++;
	*cmd = (*cmd)->next;
}

int	exec(t_cmd *cmd, char ***envp, t_data *ctx)
{
	t_data	data;
	int		code;

	data.data_code = init_data(&data, cmd, ctx, *envp);
	if (data.data_code != 0)
		return (data.data_code);
	while (cmd)
	{
		setup_signals_ignore();
		data.open_code = open_redirs(cmd->redirs, &data);
		if (data.open_code != 0)
		{
			code = handle_open_err(&data, &cmd);
			if (code != -1)
				return (code);
			continue ;
		}
		code = dispatch_cmd(cmd, envp, &data);
		if (code != -1)
			return (code);
		next_command(&data, &cmd);
	}
	return (wait_and_return(data));
}
