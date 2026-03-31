/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnicolas <mnicolas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 14:37:29 by mnicolas          #+#    #+#             */
/*   Updated: 2026/03/31 18:08:21 by mnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int open_redirs_in(t_node *redirs, t_data *data)
{
	if (!redirs && data->infd != -2)
		data->infd = data->pipefd[0];
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
			if (get_lines(redirs->str, data) == 130)
				return (130);
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
