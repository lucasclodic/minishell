/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnicolas <mnicolas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 17:26:16 by mnicolas          #+#    #+#             */
/*   Updated: 2026/03/30 15:46:34 by mnicolas         ###   ########.fr       */
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
	freee_cmds(cmd);
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

int	wait_and_return(t_data data)
{
	int	i;
	int	status;
	int	exit_code;

	i = 0;
	while (i < data.cmd_count)
	{
		waitpid(data.pid[i], &status, 0);
		if (i == data.cmd_count - 1)
		{
			setup_signals_interactive();
			if (WIFEXITED(status))
				exit_code = (WEXITSTATUS(status));
			else if (WIFSIGNALED(status))
				exit_code = (128 + WTERMSIG(status));
			else
				exit_code = 1;
		}
		i++;
	}
	free(data.pid);
	return (exit_code);
}
