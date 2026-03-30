/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclodic <lclodic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:37:36 by lclodic           #+#    #+#             */
/*   Updated: 2025/11/04 15:54:58 by lclodic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

static int	ft_strlen_temp(const char*s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len_s1;
	int		len_s2;
	char	*output;
	int		i;
	int		j;

	len_s1 = ft_strlen_temp(s1);
	len_s2 = ft_strlen_temp(s2);
	output = malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (output == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		output[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		output[i++] = s2[j++];
	output[i] = '\0';
	return (output);
}

// int main()
// {
// 	char *s1 = "Lucas";
// 	char *s2 = "Lucas";
// 	char *output = ft_strjoin(s1, s2);
// 	printf("%s\n", output);
// }
