/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclodic <lclodic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 14:44:17 by mnicolas          #+#    #+#             */
/*   Updated: 2026/04/15 17:00:04 by lclodic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*g_gnl_buffer;

char	*readfile(int fd, ssize_t *bytes)
{
	char	*buf;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
	{
		*bytes = -2;
		return (NULL);
	}
	*bytes = read(fd, buf, BUFFER_SIZE);
	if (*bytes <= 0)
	{
		free(buf);
		return (NULL);
	}
	buf[*bytes] = '\0';
	return (buf);
}

char	*end(char **buffer, ssize_t *bytes)
{
	char	*substr;

	substr = NULL;
	if (*bytes < 0)
	{
		free(*buffer);
		*buffer = NULL;
		return (NULL);
	}
	if (*bytes == 0 && !(*buffer))
		return (NULL);
	if (*buffer && **buffer)
	{
		substr = ftt_strdup(*buffer);
		if (!substr)
		{
			free(*buffer);
			*buffer = NULL;
			return (NULL);
		}
	}
	free(*buffer);
	*buffer = NULL;
	return (substr);
}

char	*line(char **buffer)
{
	char	*newline;
	char	*substr;
	char	*tmp;

	newline = ftt_strchr(*buffer, '\n');
	substr = ftt_substr(*buffer, 0, (newline - *buffer) + 1);
	if (!substr)
	{
		free(*buffer);
		*buffer = NULL;
		return (NULL);
	}
	tmp = *buffer;
	if (*(newline + 1))
	{
		*buffer = ftt_strdup(newline + 1);
		if (!(*buffer))
			return (free_and_null(buffer, substr, tmp));
	}
	else
		*buffer = NULL;
	free(tmp);
	return (substr);
}

void	free_gnl_buffer(void)
{
	if (g_gnl_buffer)
	{
		free(g_gnl_buffer);
		g_gnl_buffer = NULL;
	}
}

char	*get_next_line(int fd)
{
	char	*tmp;
	char	*rd;
	ssize_t	bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (!g_gnl_buffer || !ftt_strchr(g_gnl_buffer, '\n'))
	{
		rd = readfile(fd, &bytes);
		if (!rd)
			return (end(&g_gnl_buffer, &bytes));
		if (!g_gnl_buffer)
			g_gnl_buffer = rd;
		else
		{
			tmp = g_gnl_buffer;
			g_gnl_buffer = ftt_strjoin(g_gnl_buffer, rd);
			free(tmp);
			free(rd);
			if (!g_gnl_buffer)
				return (NULL);
		}
	}
	return (line(&g_gnl_buffer));
}
