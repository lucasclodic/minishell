/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclodic <lclodic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:37:19 by lclodic           #+#    #+#             */
/*   Updated: 2025/11/12 12:17:04 by lclodic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*dst_cast;
	const unsigned char	*src_cast;
	void				*output;
	int					i;

	if (!dst && !src)
		return (NULL);
	output = dst;
	dst_cast = dst;
	src_cast = src;
	i = 0;
	while (i < (int)n)
	{
		dst_cast[i] = src_cast[i];
		i++;
	}
	return (output);
}

// int main()
// {
// 	// char string[] = "Lucas";
// 	// char *src = &string[0];
// 	// char *dst_std = &string[2];
// 	// char *dst_ft = &string[2];
// 	// // memcpy(dst_std, src, 8);
// 	// printf("00 %s\n", dst_std);
// 	// ft_memcpy(dst_ft, src, 8);
// 	// printf("42 %s\n", dst_ft);

// 	printf("%s\n", (char *) ft_memcpy(NULL, "test", 2));
// }
