/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclodic <lclodic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:37:07 by lclodic           #+#    #+#             */
/*   Updated: 2025/11/12 13:39:09 by lclodic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <ctype.h>

int	ft_isalnum(int c)
{
	if ((c >= '0' && c <= '9'))
		return (1);
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

// int main()
// {
// 	char c = 128 + 128;
// 	printf("%d [%c]\n", c, c);
// 	// unsigned char c = 126 + 48;
// 	// printf("%d [%c]\n", c, c);
// 	printf("%d\n", ft_isalnum(200));
// 	printf("%d\n", isalnum(126 + 1));
// }
