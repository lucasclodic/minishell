/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclodic <lclodic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:37:33 by lclodic           #+#    #+#             */
/*   Updated: 2025/11/05 16:39:18 by lclodic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	int		s_size;
	char	*output;
	int		i;

	s_size = 0;
	while (s[s_size])
		s_size++;
	output = malloc(sizeof(char) * (s_size + 1));
	if (output == NULL)
		return (NULL);
	i = 0;
	while (i < s_size)
	{
		output[i] = s[i];
		i++;
	}
	output[i] = '\0';
	return (output);
}

// int main()
// {
// 	char *s1 = "Lucas";
// 	char *output_std = strdup(s1);
// 	char *output_ft = ft_strdup(s1);
// 	printf("%d\n", memcmp(output_std, output_ft, strlen(s1)));
// }
