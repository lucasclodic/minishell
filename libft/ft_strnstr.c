/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclodic <lclodic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:37:45 by lclodic           #+#    #+#             */
/*   Updated: 2025/11/05 18:24:16 by lclodic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

static int	check_word(const char *big, const char *lit, size_t i, size_t len)
{
	int	j;

	j = 0;
	while (i < len && big[i] && big[i] == lit[j] && lit[j])
	{
		i++;
		j++;
	}
	if (lit[j] == '\0')
		return (1);
	return (0);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	i = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (i < len && big[i])
	{
		if (big[i] == little[0])
		{
			if (check_word(big, little, i, len))
				return ((char *) &big[i]);
		}
		i++;
	}
	return (NULL);
}

// int main()
// {
//   char haystack[30] = "aaabcabcd";
//   char needle[10] = "aabc";
//
//   char *ptr;
//   ptr = ft_strnstr(haystack, needle, -1);
//   printf("%s\n", ptr);
// }
