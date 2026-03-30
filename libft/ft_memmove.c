/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclodic <lclodic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:37:21 by lclodic           #+#    #+#             */
/*   Updated: 2025/11/12 13:21:09 by lclodic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include "libft.h"

static void	fill(unsigned char *dst, const unsigned char *src, int i)
{
	while (0 <= (int) i)
	{
		dst[i] = src[i];
		i--;
	}
}

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char		*dst_cast;
	const unsigned char	*src_cast;
	size_t				i;

	if ((!dst && !src) || (int) n < 0)
		return (NULL);
	dst_cast = dst;
	src_cast = src;
	if (src < dst)
	{
		i = n - 1;
		fill(dst_cast, src_cast, i);
	}
	else
	{
		i = 0;
		while (n > i)
		{
			dst_cast[i] = src_cast[i];
			i++;
		}
	}
	return (dst_cast);
}

// int main()
// {
// 	char string[] = "Lucas";
// 	char *src = &string[0];
// 	char *dst = &string[2];
// 	// printf("%p\n", ft_memmove(dst, src, -1));
// 	// printf("%s\n", (char *) src);
// }
