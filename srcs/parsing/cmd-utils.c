/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd-utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclodic <lclodic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 17:09:01 by lucas             #+#    #+#             */
/*   Updated: 2026/04/15 11:33:01 by lclodic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_node	*create_redir(t_token_type type, char *filename)
{
	t_node	*redir;

	redir = malloc(sizeof(t_node));
	if (!redir)
		return (NULL);
	redir->str = ft_strdup(filename);
	if (!redir->str)
	{
		free(redir);
		return (NULL);
	}
	redir->type = type;
	redir->next = NULL;
	return (redir);
}

void	free_args(char **args, int count)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	if (!args[i])
	{
		free(args);
		return ;
	}
	while (i < count)
	{
		free(args[i]);
		i++;
	}
	free(args);
}

static void	free_one_cmd(t_cmd *cmd)
{
	int	i;

	if (cmd->args)
	{
		i = 0;
		while (cmd->args[i])
		{
			free(cmd->args[i]);
			i++;
		}
		free(cmd->args);
	}
	if (cmd->redirs)
		clean_struct(&cmd->redirs);
	free(cmd);
}

void	free_cmds(t_cmd **cmds)
{
	t_cmd	*temp;
	t_cmd	*current;

	if (!*cmds)
		return ;
	current = *cmds;
	while (current)
	{
		temp = current->next;
		free_one_cmd(current);
		current = temp;
	}
	*cmds = NULL;
}

t_node	*skip_to_pipe(t_node *tokens)
{
	while (tokens && tokens->type != PIPE)
		tokens = tokens->next;
	if (tokens)
		tokens = tokens->next;
	return (tokens);
}
