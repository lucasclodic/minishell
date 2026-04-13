/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 14:37:29 by mnicolas          #+#    #+#             */
/*   Updated: 2026/04/13 13:13:34 by lucas            ###   ########.fr       */
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
			perror("pipe");
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
			perror(redirs->str);
			return (-1);
		}
	}
	return (0);
}

int	create_pipe(t_node *redirs, t_data *data)
{
	if (!redirs)
	{
		if (data->i == data->cmd_count - 1) // ici on regarde si c'est la dernière commande
			data->outfd = 1;
		else
		{
			if (pipe(data->pipefd) == -1)
			{
				perror("pipe");
				return (-1);
			}
			data->outfd = data->pipefd[1];
		}
	}
	return (0);
}

int	open_redirs(t_node *redirs, t_data *data)
{
	int	redirs_in;
	int	redirs_out;

	redirs_in = 0;
	redirs_out = 0;
	data->outfd = -2;
	while (redirs)
	{
		if (redirs->type == REDIR_IN || redirs->type == HEREDOC)
		{
			if (close_and_handle_infile(redirs, data) == -1)
				return (-1);
			if (redirs->type == HEREDOC)
			{
				data->here_doc_code = handle_here_doc(redirs, data);
				if (data->here_doc_code != 0)
					return (data->here_doc_code);
			}
			redirs_in = 1;
		}
		else if (redirs->type == REDIR_OUT || redirs->type == APPEND)
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
				return (-1);
			}
			redirs_out = 1;
		}
		redirs = redirs->next;
	}
	if (data->here_doc == 1)
	{
		data->infd = data->pipefd[0];
		data->here_doc = 0;
	}
	if (!redirs_in)
	{
		if (data->infd != -2)
			data->infd = data->pipefd[0];
		else
			data->infd = 0;
	}
	if (!redirs_out)
	{
		if (create_pipe(NULL, data) == -1)
			return (-1);
	}
	return (0);
}

int	open_redirs_out(t_node *redirs, t_data *data)
{
	data->outfd = -2;
	while (redirs && (redirs->type == REDIR_IN || redirs->type == HEREDOC))
		redirs = redirs->next;
	if (create_pipe(redirs, data) == -1)
		return (-1);
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
			return (-1);
		}
		redirs = redirs->next;
	}
	return (0);
}
