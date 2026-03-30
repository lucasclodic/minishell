/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclodic <lclodic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:37:22 by lclodic           #+#    #+#             */
/*   Updated: 2025/11/04 16:00:47 by lclodic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*output;
	int				i;

	output = (unsigned char *)b;
	i = 0;
	while (i < (int)len)
	{
		output[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

// int main()
// {
// 	int src12_ft[5];
// 	int src12_std[5];
// 	ft_memset(src12_ft, 0, sizeof(src12_ft));
// 	memset(src12_std, 0, sizeof(src12_std));

// 	printf("%lu\n", sizeof(src12_ft));
// 	printf("%lu\n", sizeof(src12_std));
// 	printf("%d\n", memcmp(src12_ft, src12_std, 5));
// }
