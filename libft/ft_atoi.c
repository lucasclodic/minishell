/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclodic <lclodic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:37:01 by lclodic           #+#    #+#             */
/*   Updated: 2025/11/05 18:21:45 by lclodic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	ft_atoi(const char *nptr)
{
	long int	output;
	int			final_output;
	int			signe;
	int			i;

	i = 0;
	signe = 1;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			signe *= -1;
		i++;
	}
	output = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		output = output * 10 + nptr[i] - '0';
		i++;
	}
	final_output = output * signe;
	return (final_output);
}

// int main()
// {
// 	char string[] = "+   58";
// 	printf("%d\n", ft_atoi(string));
// 	printf("%d\n", atoi(string));
// }
