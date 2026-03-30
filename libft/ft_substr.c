/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclodic <lclodic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:37:51 by lclodic           #+#    #+#             */
/*   Updated: 2025/11/05 18:22:49 by lclodic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static size_t	s_strlen(char const *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*output;
	size_t	i;

	if (!s)
		return (NULL);
	if (start >= s_strlen(s))
	{
		output = malloc(1);
		if (output)
			output[0] = '\0';
		return (output);
	}
	if (start + len > s_strlen(s))
		len = s_strlen(s) - start;
	output = malloc(len + 1);
	if (!output)
		return (NULL);
	i = 0;
	while (i < len)
	{
		output[i] = s[start + i];
		i++;
	}
	output[i] = '\0';
	return (output);
}

// int main()
// {
// 	char s[] = "tripouille";
// 	char *output = ft_substr(s, 1, 1);
// 	printf("%s\n", output);
// 	printf("%d\n", strcmp(output, "r"));
// 	// printf("%p\n", s_len("Lucas", 3, 2));
// }
