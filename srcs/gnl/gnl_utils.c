/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnicolas <mnicolas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 16:25:02 by mnicolas          #+#    #+#             */
/*   Updated: 2026/04/15 14:13:26 by mnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	len(const char *s)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
	{
		i++;
	}
	return (i);
}

char	*ftt_strjoin(const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;
	char	*s;

	s = malloc(len(s1) + len(s2) + 1);
	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	while (s1 && s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		s[i + j] = s2[j];
		j++;
	}
	s[i + j] = '\0';
	return (s);
}

char	*ftt_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if ((const unsigned char)s[i] == (const unsigned char)c)
			return ((char *)(s + i));
		i++;
	}
	if ((const unsigned char)s[i] == (unsigned char)c)
		return ((char *)(s + i));
	return (NULL);
}

char	*ftt_strdup(const char *s1)
{
	char	*s2;
	size_t	i;

	i = 0;
	if (!s1)
		return (NULL);
	while (s1[i])
		i++;
	s2 = malloc(i * sizeof(char) + 1);
	if (!s2)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char	*ftt_substr(char const *s, size_t start, size_t len)
{
	char	*subs;
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	if (start >= i)
	{
		subs = malloc(1);
		if (!subs)
			return (NULL);
		subs[0] = '\0';
		return (subs);
	}
	i = 0;
	while (s[start + i] && i < len)
		i++;
	subs = malloc(i + 1);
	if (!subs)
		return (NULL);
	subs[i] = '\0';
	while (i--)
		subs[i] = s[start + i];
	return (subs);
}
