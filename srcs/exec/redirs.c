/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclodic <lclodic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 14:37:29 by mnicolas          #+#    #+#             */
/*   Updated: 2026/04/15 14:01:44 by lclodic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_here_doc(t_node *redirs, t_data *data)
{
	if (redirs->type == HEREDOC)
	{
		setup_signals_interactive();
		if (pipe(data->pipefd) == -1)
		{
			shell_perror("pipe");
			return (-1);
		}
		if (get_lines(redirs->str, data) == 130)
			return (130);
		data->here_doc = 1;
		setup_signals_ignore();
	}
	return (0);
}

int	close_and_handle_infile(t_node *redirs, t_data *data)
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
			shell_perror(redirs->str);
			return (-1);
		}
	}
	return (0);
}

int	create_pipe(t_data *data)
{
	if (data->i == data->cmd_count - 1)
	{
		if (data->outfd == -2)
			data->outfd = 1;
		return (0);
	}
	if (pipe(data->pipefd) == -1)
	{
		shell_perror("pipe");
		return (-1);
	}
	if (data->outfd == -2)
		data->outfd = data->pipefd[1];
	else
		close(data->pipefd[1]);
	return (0);
}

int	handle_input_redir(t_node *redirs, t_data *data)
{
	if (close_and_handle_infile(redirs, data) == -1)
		return (-1);
	if (redirs->type == HEREDOC)
	{
		data->here_doc_code = handle_here_doc(redirs, data);
		if (data->here_doc_code != 0)
			return (data->here_doc_code);
	}
	return (0);
}

int	open_redirs(t_node *redirs, t_data *data)
{
	int	redirs_in;
	int	ret;

	redirs_in = 0;
	data->outfd = -2;
	while (redirs)
	{
		if (redirs->type == REDIR_IN || redirs->type == HEREDOC)
		{
			ret = handle_input_redir(redirs, data);
			if (ret != 0)
				return (ret);
			redirs_in = 1;
		}
		else if ((redirs->type == REDIR_OUT || redirs->type == APPEND)
			&& handle_outfile(redirs, data) == -1)
			return (-1);
		redirs = redirs->next;
	}
	finalize_infd(data, redirs_in);
	if (create_pipe(data) == -1)
		return (-1);
	return (0);
}
