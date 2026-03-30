/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclodic <lclodic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:37:42 by lclodic           #+#    #+#             */
/*   Updated: 2025/11/04 16:04:34 by lclodic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

static int	temp_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

// static char func_test(unsigned int i, char c)
// {
// 	i = 1;
// 	return (c + i);
// }

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		len_output;
	char	*output;
	int		i;

	len_output = temp_strlen((char *)s);
	output = malloc(sizeof(char) * (len_output + 1));
	if (output == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		output[i] = s[i];
		output[i] = f(i, output[i]);
		i++;
	}
	output[i] = '\0';
	return (output);
}

// int main()
// {
// 	char *out = ft_strmapi("Lucas", &func_test);
// 	printf("%s\n", out);
// }
