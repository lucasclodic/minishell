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

static void	heredoc_write(char *line, t_data *data, int quoted)
{
	char	*expanded;

	if (quoted)
	{
		write(data->pipefd[1], line, ft_strlen(line));
		write(data->pipefd[1], "\n", 1);
		return ;
	}
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

static char	*clean_delim(char *delim, int *quoted)
{
	char	*res;
	int		i;
	int		j;

	*quoted = 0;
	i = 0;
	while (delim[i] && delim[i] != '\'' && delim[i] != '"')
		i++;
	if (!delim[i])
		return (ft_strdup(delim));
	*quoted = 1;
	res = malloc(ft_strlen(delim) + 1);
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (delim[i])
	{
		if (delim[i] != '\'' && delim[i] != '"')
			res[j++] = delim[i];
		i++;
	}
	res[j] = '\0';
	return (res);
}

static int	heredoc_loop(char *clean, int quoted, t_data *data)
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
		if (!line || ft_strcmp(line, clean) == 0)
		{
			free(line);
			break ;
		}
		heredoc_write(line, data, quoted);
		free(line);
	}
	close(data->pipefd[1]);
	return (0);
}

int	get_lines(char *delim, t_data *data)
{
	char	*clean;
	int		quoted;
	int		ret;

	clean = clean_delim(delim, &quoted);
	if (!clean)
	{
		close(data->pipefd[1]);
		return (0);
	}
	ret = heredoc_loop(clean, quoted, data);
	free(clean);
	return (ret);
}
