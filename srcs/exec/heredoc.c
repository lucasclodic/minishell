/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclodic <lclodic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 20:10:00 by lclodic           #+#    #+#             */
/*   Updated: 2026/04/15 20:10:00 by lclodic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*heredoc_read(void)
{
	char	*line;
	int		len;

	if (isatty(STDIN_FILENO))
		return (readline("> "));
	line = get_next_line(0);
	if (line)
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
	}
	return (line);
}

static void	heredoc_write(char *line, t_data *data)
{
	char	*expanded;

	expanded = expand_heredoc(line, data->env, data->exit_status);
	if (expanded)
	{
		write(data->pipefd[1], expanded, ft_strlen(expanded));
		free(expanded);
	}
	else
		write(data->pipefd[1], line, ft_strlen(line));
	write(data->pipefd[1], "\n", 1);
}

int	get_lines(char *delim, t_data *data)
{
	char	*line;

	while (1)
	{
		line = heredoc_read();
		if (g_signal == SIGINT)
		{
			g_signal = 0;
			free(line);
			close(data->pipefd[0]);
			close(data->pipefd[1]);
			return (130);
		}
		if (!line || ft_strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		heredoc_write(line, data);
		free(line);
	}
	close(data->pipefd[1]);
	return (0);
}
