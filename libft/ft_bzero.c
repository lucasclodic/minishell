/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclodic <lclodic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:37:03 by lclodic           #+#    #+#             */
/*   Updated: 2025/11/12 10:00:49 by lclodic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*cast;
	size_t			i;

	cast = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		cast[i] = 0;
		i++;
	}
}

// int main()
// {
// 	int string[] = {1, 2, 3, 4};
// 	ft_bzero(string, sizeof(string));
// 	printf("siz %ld\n", sizeof(string));
// 	int i = 0;
// 	while (i < 4)
// 	{
// 		printf("%d\n", string[i]);
// 		i++;
// 	}
// }
