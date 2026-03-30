/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclodic <lclodic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:37:14 by lclodic           #+#    #+#             */
/*   Updated: 2025/11/05 16:35:22 by lclodic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*s_casted;
	unsigned char		c_casted;

	s_casted = s;
	c_casted = c;
	i = 0;
	while (n != 0 && i < (n - 1) && s_casted[i] != c_casted)
		i++;
	if (n == 0)
		return (NULL);
	if (s_casted[i] == c_casted)
		return ((void *) &(s_casted[i]));
	return (NULL);
}

// int main()
// {
// 	char *str = "Lucas";
// 	char c = 'u';
// 	int n = 3;
// 	char *ft_output = memchr(str, c, n);
// 	char *str_output = memchr(str, c, n);
// 	printf("%d\n", memcmp(ft_output, str_output, 5));
// }
