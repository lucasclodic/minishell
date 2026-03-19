/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 17:08:58 by lucas             #+#    #+#             */
/*   Updated: 2026/03/19 17:08:59 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TO BE DELETED
static void	display_cmds(t_cmd *cmds)
{
	int	i;
	int	cmd_nb;

	cmd_nb = 1;
	while (cmds)
	{
		printf("=== CMD %d ===\n", cmd_nb);
		if (cmds->args)
		{
			i = 0;
			while (cmds->args[i])
			{
				printf("  arg[%d]: %s\n", i, cmds->args[i]);
				i++;
			}
		}
		if (cmds->redirs)
		{
			t_node *tmp = cmds->redirs;
			printf("  redirs:\n");
			while (tmp)
			{
				printf("    type=%d file=%s\n", tmp->type, tmp->str);
				tmp = tmp->next;
			}
		}
		cmds = cmds->next;
		cmd_nb++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_node	*tokens;
	t_cmd	*cmds;
	char	*str;

	(void)argc;
	(void)argv;
	(void)envp;
	while (1)
	{
		str = readline("minishell> ");
		if (!str)
			return (1);
		add_history(str);
		tokens = tokeniser(str);
		if (tokens)
		{
			cmds = parser(tokens);
			display_cmds(cmds);
			free_cmds(&cmds);
			clean_struct(&tokens);
		}
		free(str);
	}
}