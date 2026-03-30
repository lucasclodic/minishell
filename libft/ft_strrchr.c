/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclodic <lclodic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:37:48 by lclodic           #+#    #+#             */
/*   Updated: 2025/11/05 15:04:00 by lclodic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

char	*ft_strrchr(const char *s, int c)
{
	int				len_s;
	unsigned char	casted;

	casted = c;
	len_s = 0;
	while (*s)
	{
		s++;
		len_s++;
	}
	while (*s != casted && len_s > 0)
	{
		s--;
		len_s--;
	}
	if (*s == casted)
		return ((char *)s);
	return (NULL);
}

// int main()
// {
// 	// Test 1: Cherche 'u' dans "Lucas"
// 	const char src1[] = "Lucas";
// 	char c1 = 'z';
// 	char *ft_output1 = ft_strrchr(src1, c1);
// 	char *std_output1 = strrchr(src1, c1);
// 	printf("%d\n", std_output1 == ft_output1);
// }
