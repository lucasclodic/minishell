/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 17:09:04 by lucas             #+#    #+#             */
/*   Updated: 2026/03/23 17:58:14 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_args(t_node *tokens)
{
	int	count;

	count = 0;
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type == WORD)
			count++;
		else
			tokens = tokens->next;
		tokens = tokens->next;
	}
	return (count);
}

static char	**fill_args(t_node *tokens, int count)
{
	char	**args;
	int		i;

	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	i = 0;
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type == WORD)
		{
			args[i] = ft_strdup(tokens->str);
			if (!args[i])
			{
				free_args(args, i); 
				return (NULL);
			}
			i++;
		}
		else
			tokens = tokens->next;
		tokens = tokens->next;
	}
	args[i] = NULL;
	return (args);
}

static t_node	*fill_redirs(t_node *tokens)
{
	t_node	*redirs;
	t_node	*new;

	redirs = NULL;
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type != WORD)
		{
			new = create_redir(tokens->type, tokens->next->str);
			if (!new)
			{
				clean_struct(&redirs);
				return (NULL);
			}
			add_node_to_main(&redirs, new);
			tokens = tokens->next;
		}
		tokens = tokens->next;
	}
	return (redirs);
}

static t_cmd	*create_cmd(t_node *tokens)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = fill_args(tokens, count_args(tokens));
	if (!cmd->args)
	{
		free(cmd);
		return (NULL);
	}
	cmd->redirs = fill_redirs(tokens);
	cmd->next = NULL;
	return (cmd);
}

static t_node	*skip_to_pipe(t_node *tokens)
{
	while (tokens && tokens->type != PIPE)
		tokens = tokens->next;
	if (tokens)
		tokens = tokens->next;
	return (tokens);
}

t_cmd	*parser(t_node *tokens)
{
	t_cmd	*cmds;
	t_cmd	*current;
	t_cmd	*new;

	cmds = NULL;
	while (tokens)
	{
		new = create_cmd(tokens);
		if (!new)
		{
			free_cmds(&cmds);
			return (NULL);
		}
		if (!cmds)
		{
			cmds = new;
			current = new;
		}
		else
		{
			current->next = new;
			current = new;
		}
		tokens = skip_to_pipe(tokens);
	}
	return (cmds);
}
