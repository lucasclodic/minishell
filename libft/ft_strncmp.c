/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclodic <lclodic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:37:43 by lclodic           #+#    #+#             */
/*   Updated: 2025/11/05 16:30:57 by lclodic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (n != 0 && i < (n - 1) && s1[i] && s1[i] == s2[i])
		i++;
	if (n == 0)
		return (0);
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}

// int main()
// {
// 	printf("%d\n", ft_strncmp("t", "", 0));
// 	printf("%d\n", strncmp("t", "", 0));
// }
