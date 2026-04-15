/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclodic <lclodic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 17:40:00 by lclodic           #+#    #+#             */
/*   Updated: 2026/04/15 17:40:00 by lclodic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_outfile(t_node *redirs, t_data *data)
{
	if (data->outfd != -2)
		close(data->outfd);
	if (redirs->type == APPEND)
		data->outfd = open(redirs->str,
				O_WRONLY | O_APPEND | O_CREAT, 0644);
	else
		data->outfd = open(redirs->str,
				O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (data->outfd == -1)
		return (shell_perror(redirs->str), -1);
	return (0);
}

void	finalize_infd(t_data *data, int redirs_in)
{
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
}
