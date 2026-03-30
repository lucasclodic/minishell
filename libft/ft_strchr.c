/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclodic <lclodic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:37:32 by lclodic           #+#    #+#             */
/*   Updated: 2025/11/05 15:03:47 by lclodic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

char	*ft_strchr(const char *s, int c)
{
	unsigned char	casted;

	casted = c;
	while (*s != casted && *s)
		s++;
	if (*s == casted)
		return ((char *)s);
	return (NULL);
}

// int main()
// {
// 	char string[] = "tripouille";
// 	char c = 0;

// 	printf("%s [%p] \n", ft_strchr(string, c), ft_strchr(string, c));
// 	printf("%s [%p] \n", strchr(string, c), strchr(string, c));

// }
