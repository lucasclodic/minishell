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

static int	append_read(char **buffer, char *rd)
{
	char	*tmp;

	if (!*buffer)
	{
		*buffer = rd;
		return (0);
	}
	tmp = *buffer;
	*buffer = ftt_strjoin(*buffer, rd);
	free(tmp);
	free(rd);
	if (!*buffer)
		return (-1);
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*rd;
	ssize_t		bytes;

	if (fd < 0)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	while (!buffer || !ftt_strchr(buffer, '\n'))
	{
		rd = readfile(fd, &bytes);
		if (!rd)
			return (end(&buffer, &bytes));
		if (append_read(&buffer, rd) < 0)
			return (NULL);
	}
	return (line(&buffer));
}

void	free_gnl_buffer(void)
{
	get_next_line(-1);
}
