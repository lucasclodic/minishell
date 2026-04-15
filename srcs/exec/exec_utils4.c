/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclodic <lclodic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 17:35:00 by lclodic           #+#    #+#             */
/*   Updated: 2026/04/15 17:35:00 by lclodic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <sys/stat.h>

int	compute_exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

void	check_is_dir(char *path, t_cmd *cmds, char **envp, t_data data)
{
	struct stat	st;

	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
	{
		print_error(cmds->args[0], NULL, "Is a directory");
		if (data.exec_mode == 1)
			free(path);
		child_cleanup_and_exit(cmds, envp, data, 126);
	}
}

static int	heredoc_len(char *line, t_expand *e)
{
	int		i;
	int		len;
	char	*val;

	i = 0;
	len = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1])
		{
			val = get_var_value(line, &i, e);
			if (val)
			{
				len += ft_strlen(val);
				free(val);
			}
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

static void	heredoc_fill(char *line, char *res, t_expand *e)
{
	int		k;
	char	*val;

	e->i = 0;
	e->j = 0;
	while (line[e->i])
	{
		if (line[e->i] == '$' && line[e->i + 1])
		{
			val = get_var_value(line, &e->i, e);
			if (val)
			{
				k = 0;
				while (val[k])
					res[e->j++] = val[k++];
				free(val);
			}
		}
		else
			res[e->j++] = line[e->i++];
	}
	res[e->j] = '\0';
}

char	*expand_heredoc(char *line, char **env, int exit_status)
{
	t_expand	e;
	char		*res;
	int			len;

	e.env = env;
	e.exit_status = exit_status;
	e.quote = 0;
	len = heredoc_len(line, &e);
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	heredoc_fill(line, res, &e);
	return (res);
}
