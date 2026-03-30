/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclodic <lclodic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:37:30 by lclodic           #+#    #+#             */
/*   Updated: 2025/11/12 13:24:43 by lclodic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define RESET "\033[0m"

static int	count_str(char const *s, char c)
{
	int	output;
	int	i;

	i = 0;
	output = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			output++;
		i++;
	}
	return (output);
}

static int	calc_taille_ligne(char const *s, char c, int i)
{
	int	i_temp;

	i_temp = i;
	while (s[i_temp] != c && s[i_temp])
		i_temp++;
	return (i_temp - i);
}

static void	fill_line(char const *s, char c, char *output, int i)
{
	int	i_out;

	i_out = 0;
	while (s[i] != c && s[i])
	{
		output[i_out] = s[i];
		i_out++;
		i++;
	}
	output[i_out] = '\0';
}

static int	calc_i(char const *s, char c, int i)
{
	while (s[i] == c && s[i])
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**output;
	int		i;
	int		j;

	output = malloc(sizeof(char *) * (count_str(s, c) + 1));
	if (output == NULL)
		return (NULL);
	i = calc_i(s, c, 0);
	j = 0;
	while (s[i])
	{
		output[j] = malloc(sizeof(char) * (calc_taille_ligne(s, c, i) + 1));
		if (output[j] == NULL)
		{
			while (j-- > 0)
				free(output[j]);
			free(output);
			return (NULL);
		}
		fill_line(s, c, output[j], i);
		i = calc_i(s, c, i + calc_taille_ligne(s, c, i));
		j++;
	}
	output[j] = NULL;
	return (output);
}
