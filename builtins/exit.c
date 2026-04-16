/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 10:00:00 by lucas             #+#    #+#             */
/*   Updated: 2026/03/24 10:00:00 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	parse_long(const char *str, long *out)
{
	unsigned long	acc;
	int				sign;
	int				i;

	acc = 0;
	sign = 1;
	i = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		acc = acc * 10 + (unsigned long)(str[i] - '0');
		if ((sign == 1 && acc > 9223372036854775807UL)
			|| (sign == -1 && acc > 9223372036854775808UL))
			return (0);
		i++;
	}
	*out = (long)(sign * (long)acc);
	return (1);
}

int	ft_exit(char **args, int last_status)
{
	long	code;

	if (isatty(STDIN_FILENO))
		ft_putendl_fd("exit", 2);
	if (!args[1])
		exit((unsigned char)last_status);
	if (!is_numeric(args[1]) || !parse_long(args[1], &code))
	{
		print_error("exit", args[1], "numeric argument required");
		exit(2);
	}
	if (args[2])
	{
		print_error("exit", NULL, "too many arguments");
		return (1);
	}
	exit((unsigned char)code);
	return (0);
}
