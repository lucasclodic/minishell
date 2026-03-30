/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclodic <lclodic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:37:24 by lclodic           #+#    #+#             */
/*   Updated: 2025/11/04 15:53:01 by lclodic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>    // pour open()
#include <unistd.h>   // pour read(), close()
#include <stdio.h>

void	ft_putchar_fd(char c, int fd)
{
	write (fd, &c, 1);
}

// int main()
// {
// 	int fd = open("test-ft_putchar_fd.txt", O_RDWR | O_CREAT, 0644);
// 	ft_putchar_fd('l', fd);
// 	close(fd);
// 	fd = open("test-ft_putchar_fd.txt", O_RDWR | O_CREAT, 0644);
// 	char c;
// 	read(fd, &c, 1);
// 	printf("c %c\n", c);
// }
