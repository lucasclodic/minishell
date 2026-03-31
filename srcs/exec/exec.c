/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 18:35:05 by mnicolas          #+#    #+#             */
/*   Updated: 2026/03/31 11:31:28 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	work_child(t_cmd *cmd, char **envp, t_data data)
{
	if (dup2(data.infd, 0) == -1)
	{
		close(data.infd);
		free(data.pid);
		free_cmds(&cmd);
		free_perror_exit("dup2", data);
	}
	if (dup2(data.outfd, 1) == -1)
	{
		close(data.outfd);
		free(data.pid);
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

int	count_cmds(t_cmd *cmds)
{
	int i;
	t_cmd *tmp;

	tmp = cmds;
	i = 0;
	while(tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0')
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	get_lines(char *delim, t_data *data)
{
	char	*line;

	line = readline("> ");
	while (line && ft_strcmp(line, delim) != 0) //if !line
	{
		write(data->pipefd[1], line, strlen(line));
		write(data->pipefd[1], "\n", 1);
		free(line);
		line = readline("> ");
	}
	free(line);
	close(data->pipefd[1]);
}

int open_redirs_in(t_node *redirs, t_data *data)
{
	if (!redirs && data->infd != -2)
		return (0);
	while(redirs && (redirs->type == REDIR_IN || redirs->type == HEREDOC))
	{
		if (data->here_doc == 1)
		{
			close(data->pipefd[0]);
			data->here_doc = 0;
		}
		if (data->infd != -2)
			close(data->infd);
		if (redirs->type == REDIR_IN)
		{
			data->infd = open(redirs->str, O_RDONLY);
			if (data->infd == -1)
			{
				perror(redirs->str);
				return (-1);
			}
		}
		else if (redirs->type == HEREDOC)
		{
			setup_signals_interactive();
			if (pipe(data->pipefd) == -1)
			{
				perror("pipe");
				return(-1);
			}
			get_lines(redirs->str, data);
			data->here_doc = 1;
			setup_signals_ignore();
		}
		redirs = redirs->next;
	}
	if (data->here_doc == 1)
	{
		data->infd = data->pipefd[0];
		data->here_doc = 0;
	}
	if (data->infd == -2)
		data->infd = 0;
	return (0);
}

int open_redirs_out(t_node *redirs, t_data *data)
{
	data->outfd = -2;
	while (redirs && (redirs->type == REDIR_IN || redirs->type == HEREDOC))
		redirs = redirs->next;
	if (!redirs)
	{
		if (data->i == data->cmd_count - 1)
			data->outfd = 1;
		else
		{
			if (pipe(data->pipefd) == -1)
			{
				perror("pipe");
				return(-1);
			}
			data->outfd = data->pipefd[1];
		}
	}
	while (redirs && (redirs->type == REDIR_OUT || redirs->type == APPEND))
	{
		if (data->outfd != -2)
			close(data->outfd);
		if (redirs->type == APPEND)
			data->outfd = open(redirs->str,
					O_WRONLY | O_APPEND | O_CREAT, 0644);
		else if (redirs->type == REDIR_OUT)
			data->outfd = open(redirs->str,
					O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (data->outfd == -1)
		{
			perror(redirs->str);
			return(-1);
		}
		redirs = redirs->next;
	}
	return (0);
}

int execute_builtin(t_cmd *cmd, char **envp, t_data data)
{
	if (dup2(data.infd, 0) == -1)
	{
		close(data.infd);
		free(data.pid);
		free_cmds(&cmd);
		free_perror_exit("dup2", data);
	}
	if (dup2(data.outfd, 1) == -1)
	{
		close(data.outfd);
		free(data.pid);
		free_cmds(&cmd);
		free_perror_exit("dup2", data);
	}
	return(exec_builtin(cmd, &envp));
}

int	exec(t_cmd *cmds, char **envp)
{
	t_data	data;
	t_cmd *cmd;
	int	exit_c;

	cmd = cmds;
	data.i = 0;
	data.infd = -2;
	data.here_doc = 0;
	data.cmd_count = count_cmds(cmd);
	data.pid = malloc(data.cmd_count * sizeof(pid_t));
	if (!data.pid)
	{
		perror("malloc");
		free_cmds(&cmds);
		return (1);
	}
	while (cmd)
	{
		setup_signals_ignore();
		open_redirs_in(cmd->redirs, &data);
		if (data.infd == -1) //data.infd = open("/dev/null", O_RDONLY)
		{
			free(data.pid);
			free_cmds(&cmds);
			return (1);
		}
		open_redirs_out(cmd->redirs, &data);
		if (data.outfd == -1)
		{
			free(data.pid);
			free_cmds(&cmds);
			return (1);
		}
		if (is_builtin(cmd->args[0]))
		{
			exit_c = execute_builtin(cmd, envp, data);
			if (!cmd->next)
				return (exit_c);
		}
		else
			fork_child(cmd, &data, envp);
		if (data.infd > 2)
			close(data.infd);
		if (data.outfd > 2)
			close(data.outfd);
		if (data.i != data.cmd_count - 1)//!cmd->next
			data.infd = data.pipefd[0];
		data.i++;
		cmd = cmd->next;
	}
	return (wait_and_return(data));
}
