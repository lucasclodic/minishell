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

int	init_data(t_data *data, t_cmd *cmd, t_data *ctx, char **env)
{
	int	i;

	data->i = 0;
	data->infd = -2;
	data->outfd = -2;
	data->pipefd[0] = -2;
	data->pipefd[1] = -2;
	data->here_doc = 0;
	data->exec_mode = 0;
	data->str_ref = ctx->str_ref;
	data->tokens_ref = ctx->tokens_ref;
	data->exit_status = ctx->exit_status;
	data->env = env;
	data->cmd_count = count_cmds(cmd);
	data->pid = malloc(data->cmd_count * sizeof(pid_t));
	if (!data->pid)
		return (shell_perror("malloc"), 1);
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
