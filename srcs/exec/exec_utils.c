/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnicolas <mnicolas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 17:26:16 by mnicolas          #+#    #+#             */
/*   Updated: 2026/04/01 13:09:18 by mnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cmd_not_found(char *str)
{
	ft_putstr_fd("command not found: ", 2);
	ft_putendl_fd(str, 2);
}

void	free_and_exit(t_cmd *cmd, int exit_code)
{
	free_cmds(&cmd);
	exit(exit_code);
}

void	*free_words(char **words)
{
	int	j;

	j = 0;
	if (!words)
		return (NULL);
	while (words[j])
	{
		free(words[j]);
		j++;
	}
	free(words);
	return (NULL);
}

void	free_perror_exit(char *str, t_data data)
{
	free(data.pid);
	perror(str);
	exit(1);
}

int	free_perror_return(char *str)
{
	perror(str);
	return (-1);
}
