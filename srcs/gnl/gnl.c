/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnicolas <mnicolas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 14:44:17 by mnicolas          #+#    #+#             */
/*   Updated: 2026/04/15 14:13:36 by mnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*free_and_null(char **buf, char *s, char *t)
{
	free(s);
	free(t);
	*buf = NULL;
	return (NULL);
}

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
	substr = ftt_substr(*buffer, 0, (newline - *buffer) + 1);//+1
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

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*tmp;
	char		*rd;
	ssize_t		bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (!buffer || !ftt_strchr(buffer, '\n'))
	{
		rd = readfile(fd, &bytes);
		if (!rd)
			return (end(&buffer, &bytes));
		if (!buffer)
			buffer = rd;
		else
		{
			tmp = buffer;
			buffer = ftt_strjoin(buffer, rd);
			free(tmp);
			free(rd);
			if (!buffer)
				return (NULL);
		}
	}
	return (line(&buffer));
}
