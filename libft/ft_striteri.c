/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclodic <lclodic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:37:34 by lclodic           #+#    #+#             */
/*   Updated: 2025/11/04 15:54:34 by lclodic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

// void func_test(unsigned int i, char * c)
// {
// 	i = 1;
// 	*c = *c + i;
// }

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;

	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
	s[i] = '\0';
}

// int main()
// {
// 	char string[] = "Lucas";
// 	printf("avant : %s\n", string);
// 	ft_striteri(string, &func_test);
// 	printf("apres : %s\n", string);
// }
