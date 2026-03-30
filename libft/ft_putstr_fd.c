/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclodic <lclodic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:37:28 by lclodic           #+#    #+#             */
/*   Updated: 2025/11/04 15:53:28 by lclodic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>    // pour open()
#include <unistd.h>   // pour read(), close()
#include <stdio.h>

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write (fd, &s[i], 1);
		i++;
	}
}

// int main()
// {
// 	int fd = open("test-ft_putstr_fd.txt", O_RDWR | O_CREAT, 0644);
// 	ft_putstr_fd("Lucas", fd);
// 	close(fd);
// 	fd = open("test-ft_putstr_fd.txt", O_RDWR | O_CREAT, 0644);
// 	char check[400];
// 	read(fd, check, 6);
// 	printf("%s\n", check);
// 	close(fd);
// }
