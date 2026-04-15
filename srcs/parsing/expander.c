/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclodic <lclodic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 10:31:11 by lucas             #+#    #+#             */
/*   Updated: 2026/04/15 11:37:43 by lclodic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	remove_empty_args(char **args, int i, char *expanded)
{
	int	j;

	j = i + 1;
	free(args[i]);
	while (args[j])
	{
		args[j - 1] = args[j];
		j++;
	}
	args[j - 1] = NULL;
	free(expanded);
}

static int	expand_args(t_cmd *cmd, t_expand *e)
{
	int		i;
	char	*expanded;

	i = 0;
	while (cmd->args[i])
	{
		expanded = expand_str(cmd->args[i], e);
		if (!expanded)
			return (0);
		if (!expanded[0] && !ft_strchr(cmd->args[i], '\'')
			&& !ft_strchr(cmd->args[i], '"'))
			remove_empty_args(cmd->args, i, expanded);
		else
		{
			free(cmd->args[i]);
			cmd->args[i] = expanded;
			i++;
		}
	}
	return (1);
}

static int	expand_redirs(t_cmd *cmd, t_expand *e)
{
	t_node	*redir;
	char	*expanded;

	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type != HEREDOC)
		{
			expanded = expand_str(redir->str, e);
			if (!expanded)
				return (0);
			free(redir->str);
			redir->str = expanded;
		}
		redir = redir->next;
	}
	return (1);
}

int	expand_cmds(t_cmd *cmds, int exit_status, char **env)
{
	t_expand	e;

	e.exit_status = exit_status;
	e.env = env;
	while (cmds)
	{
		if (!expand_args(cmds, &e))
			return (0);
		if (!expand_redirs(cmds, &e))
			return (0);
		cmds = cmds->next;
	}
	return (1);
}
