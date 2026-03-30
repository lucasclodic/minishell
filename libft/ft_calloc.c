/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclodic <lclodic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:37:05 by lclodic           #+#    #+#             */
/*   Updated: 2025/11/12 11:39:00 by lclodic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*output;
	unsigned char	*cast;
	size_t			i;

	if (nmemb != 0 && size > SIZE_MAX / nmemb)
		return (NULL);
	output = malloc(nmemb * size);
	if (output == NULL)
		return (NULL);
	cast = (unsigned char *)output;
	i = 0;
	while (i < (nmemb * size))
	{
		cast[i] = 0;
		i++;
	}
	return (output);
}

// int main(void)
// {
// 	char *string = ft_calloc(10, 0);
// 	free(string);
// 	// int i = 0;
// 	// while (i < (10 - 1))
// 	// {
// 	// 	string[i] = 'l';
// 	// 	i++;
// 	// }
// 	// // string[i] = '\0';
// 	// printf("%s\n", string);
// }
