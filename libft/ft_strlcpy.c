/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclodic <lclodic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:37:39 by lclodic           #+#    #+#             */
/*   Updated: 2025/11/05 14:14:37 by lclodic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (dstsize != 0 && i < (dstsize - 1) && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize > 0)
		dst[i] = '\0';
	while (src[i])
		i++;
	return (i);
}

// int main()
// {
// 	char dst[10];
// 	printf("%ld\n", ft_strlcpy(dst, "Hello", 0));
// 	printf("%ld\n", ft_strlcpy(dst, "Hello", 1));
// 	printf("%ld\n", ft_strlcpy(dst, "Hello", 3));
// }
