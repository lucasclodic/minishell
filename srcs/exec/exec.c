/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnicolas <mnicolas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 18:35:05 by mnicolas          #+#    #+#             */
/*   Updated: 2026/03/31 18:17:16 by mnicolas         ###   ########.fr       */
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

int execute_builtin(t_cmd *cmd, char **envp, t_data data)
{
	int exit_c;
	int stdin_backup;
    int stdout_backup;

	setup_signals_interactive();
	stdin_backup = dup(0);
    stdout_backup = dup(1);
	if (stdin_backup == -1 || stdout_backup == -1)
	{
		close(stdin_backup);
		close(stdout_backup);
		free_perror_return("dup");
	}
	if (dup2(data.infd, 0) == -1 || (dup2(data.outfd, 1) == -1))
	{
		if (data.infd > 2)
			close(data.infd);
		if (data.outfd > 2)
			close(data.outfd);
		close(stdin_backup);
		close(stdout_backup);
		free_perror_return("dup2");
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

int	exec(t_cmd *cmds, char **envp)
{
	t_data	data;
	t_cmd *cmd;
	int open_code;

	cmd = cmds;
	data.i = 0;
	data.infd = -2;
	data.here_doc = 0;
	data.cmd_count = count_cmds(cmd);
	data.pid = malloc(data.cmd_count * sizeof(pid_t));
	if (!data.pid)
	{
		perror("malloc");
		return (1);
	}
	while (cmd)
	{
		setup_signals_ignore();
		open_code = open_redirs_in(cmd->redirs, &data);
		if (open_code == -1)
		{
			if (data.infd != -1)
			{
				if (data.infd > 2)
					close(data.infd);
				if (data.outfd > 2)
					close(data.outfd);
				free(data.pid);
				setup_signals_interactive();
				return (1);
			}
			data.infd = open("/dev/null", O_RDONLY);
			if (data.infd == -1)
			{
				if (data.infd > 2)
					close(data.infd);
				if (data.outfd > 2)
					close(data.outfd);
				perror("/dev/null");
				free(data.pid);
				setup_signals_interactive();
				return (1);
			}
		}
		else if (open_code == 130)
		{
			if (data.infd > 2)
				close(data.infd);
			if (data.outfd > 2)
				close(data.outfd);
			free(data.pid);
			return (130);
		}
		if (open_redirs_out(cmd->redirs, &data) == -1)
		{
			free(data.pid);
			setup_signals_interactive();
			return (1);
		}
		if (is_builtin(cmd->args[0]) && data.cmd_count == 1)
		{
			free(data.pid);
			return(execute_builtin(cmd, envp, data));
		}
		else
		{
			if (fork_child(cmd, &data, envp) == -1)
			{
				free(data.pid);
				return (-1);
			}
		}
		if (data.infd > 2)
			close(data.infd);
		if (data.outfd > 2)
			close(data.outfd);
		data.i++;
		cmd = cmd->next;
	}
	return (wait_and_return(data));
}
