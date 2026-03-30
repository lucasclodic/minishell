/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclodic <lclodic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:37:37 by lclodic           #+#    #+#             */
/*   Updated: 2025/11/05 14:42:39 by lclodic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

size_t	ft_strlcat(char *dst, const char *src, size_t siz)
{
	size_t	i_dest;
	size_t	i_src;
	size_t	j;

	i_dest = 0;
	while (dst[i_dest] && i_dest < (siz))
		i_dest++;
	i_src = 0;
	while (siz != 0 && (i_dest < (siz - 1)) && src[i_src])
	{
		dst[i_dest] = src[i_src];
		i_dest++;
		i_src++;
	}
	if (i_dest < siz)
		dst[i_dest] = '\0';
	j = 0;
	while (src[i_src + j])
		j++;
	return (i_dest + j);
}

// int main()
// {
// 	char dest[20];
// 	printf("%s [%ld]\n", dest, ft_strlcat(dest, "Lucas", 5));
// }
