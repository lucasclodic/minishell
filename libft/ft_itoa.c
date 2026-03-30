/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclodic <lclodic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:37:13 by lclodic           #+#    #+#             */
/*   Updated: 2025/11/04 15:51:41 by lclodic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

static int	len_n(int n)
{
	long int	n_temp;
	int			len;

	len = 1;
	n_temp = n;
	if (n_temp < 0)
	{
		len++;
		n_temp = -n_temp;
	}
	while (n_temp > 9)
	{
		n_temp /= 10;
		len++;
	}
	return (len);
}

static void	fill_output(long int n, char *output, int taille_n)
{
	long int	n_temp;

	n_temp = n;
	if (n < 0)
	{
		n_temp = -n_temp;
		output[0] = '-';
	}
	output[taille_n--] = '\0';
	while (taille_n >= 0)
	{
		if (!(n < 0 && taille_n == 0))
			output[taille_n] = n_temp % 10 + '0';
		n_temp /= 10;
		taille_n--;
	}
}

char	*ft_itoa(int n)
{
	char	*output;
	int		taille_n;

	taille_n = len_n(n);
	output = malloc(sizeof(char) * (taille_n + 1));
	if (output == NULL)
		return (NULL);
	fill_output(n, output, taille_n);
	return (output);
}

// int main()
// {
// 	char *test = ft_itoa(0);
// 	printf("%s\n", test);
// }
