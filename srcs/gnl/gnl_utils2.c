/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclodic <lclodic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 17:30:00 by lclodic           #+#    #+#             */
/*   Updated: 2026/04/15 17:30:00 by lclodic          ###   ########.fr       */
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
