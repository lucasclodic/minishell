/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclodic <lclodic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:37:25 by lclodic           #+#    #+#             */
/*   Updated: 2025/11/04 16:01:11 by lclodic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>    // pour open()
#include <unistd.h>   // pour read(), close()
#include <stdio.h>

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write (fd, &s[i], 1);
		i++;
	}
	write (fd, "\n", 1);
}

// int main()w
// {
// 	int fd = open("test-ft_putendl_fd.txt", O_RDWR | O_CREAT, 0644);
// 	ft_putendl_fd("Lucas", fd);
// 	close(fd);
// 	// fd = open("test-ft_putendl_fd.txt", O_RDWR | O_CREAT, 0644);
// 	// char check[400];
// 	// read(fd, check, 6);
// 	// printf("%s\n", check);
// 	// close(fd);
// }
