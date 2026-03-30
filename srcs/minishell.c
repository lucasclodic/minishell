/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnicolas <mnicolas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 17:08:58 by lucas             #+#    #+#             */
/*   Updated: 2026/03/30 15:54:00 by mnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// static void	display_cmds(t_cmd *cmds)
// {
// 	int	i;
// 	int	cmd_nb;

// 	cmd_nb = 1;
// 	while (cmds)
// 	{
// 		printf("=== CMD %d ===\n", cmd_nb);
// 		if (cmds->args)
// 		{
// 			i = 0;
// 			while (cmds->args[i])
// 			{
// 				printf("  arg[%d]: %s\n", i, cmds->args[i]);
// 				i++;
// 			}
// 		}
// 		if (cmds->redirs)
// 		{
// 			t_node *tmp = cmds->redirs;
// 			printf("  redirs:\n");
// 			while (tmp)
// 			{
// 				printf("    type=%d file=%s\n", tmp->type, tmp->str);
// 				tmp = tmp->next;
// 			}
// 		}
// 		cmds = cmds->next;
// 		cmd_nb++;
// 	}
// }

int	main(int argc, char **argv, char **envp)
{
	t_node	*tokens;
	t_cmd	*cmds;
	char	*str;
	char	**env;
	// int exit_code;

	(void)argc;
	(void)argv;
	env = copy_env(envp); // minisehll a sa propre copie du env pour le modifier (export, unset, etc)
	if (!env)
		return (1);
	while (1)
	{
		// On active les signaux du mode interactif AVANT readline pour que ctrl-C affiche un nouveau propmpt
		if (isatty(STDIN_FILENO))
			setup_signals_interactive();
		str = readline("minishell> ");
		if (!str) // ctrl-D → readline retourne NULL → on quitte proprement
		{
			if (g_signal)  // interrupted by Ctrl-C
			{
				g_signal = 0;
				continue;
			}
			if (isatty(STDIN_FILENO))
				printf("exit\n");
			break ;
		}
		add_history(str);
		tokens = tokeniser(str);
		if (tokens)
		{
			cmds = parser(tokens);
			if (cmds)
			{
				expand_cmds(cmds, 0, env);
				exec(cmds, envp);
				// display_cmds(cmds);
				free_cmds(&cmds);
			}
			clean_struct(&tokens);
		}
		free(str);
	}
}
