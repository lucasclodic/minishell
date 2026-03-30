/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclodic <lclodic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:37:18 by lclodic           #+#    #+#             */
/*   Updated: 2025/11/05 16:36:51 by lclodic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*s1_casted;
	const unsigned char	*s2_casted;

	s1_casted = (const unsigned char *) s1;
	s2_casted = (const unsigned char *) s2;
	i = 0;
	while (n != 0 && i < (n - 1) && s1_casted[i] == s2_casted[i])
		i++;
	if (n == 0)
		return (0);
	return (s1_casted[i] - s2_casted[i]);
}

// int main()
// {
// 	char *s1 = "Lucas fait un test";
// 	char *s2 = "Sucas fait un test";
// 	int n = 19;
// 	printf("00 %d\n", memcmp(s1, s2, n));
// 	printf("42 %d\n", ft_memcmp(s1, s2, n));
// }
