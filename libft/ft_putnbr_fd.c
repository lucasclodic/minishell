/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclodic <lclodic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:37:27 by lclodic           #+#    #+#             */
/*   Updated: 2025/11/04 15:53:21 by lclodic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>    // pour open()
#include <unistd.h>   // pour read(), close()
#include <stdio.h>

static void	recurs_putnbr(long int n, int fd)
{
	char	c;

	if (n < 0)
	{
		write (fd, "-", 1);
		n = -n;
	}
	if (n > 9)
		recurs_putnbr(n / 10, fd);
	c = n % 10 + '0';
	write (fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	long int	n_long;

	n_long = n;
	recurs_putnbr(n_long, fd);
}

// int main()
// {
// 	int fd = open("test-ft_putnbr_fd.txt", O_RDWR | O_CREAT, 0644);
// 	ft_putnbr_fd(-2147483648, fd);
// }
