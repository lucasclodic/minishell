/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnicolas <mnicolas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 17:08:58 by lucas             #+#    #+#             */
/*   Updated: 2026/04/01 12:54:25 by mnicolas         ###   ########.fr       */
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

void build_prompt(char *buf)
{
    char	cwd[50];
	size_t	len;
	size_t	i;
	char	*ms;

	len = 0;
	i = 0;
	ms = "minishell> ";
    if (!getcwd(cwd, sizeof(cwd)))
        buf[0] = '\0';
	while (cwd[i])
	{
		buf[len++] = cwd[i];
		i++;
	}
	i = 0;
	buf[len++] = ' ';
	buf[len++] = '$';
	buf[len++] = ' ';
	while (ms[i])
	{
		buf[len++] = ms[i];
		i++;
	}
	buf[len] = '\0';
}

int	main(int argc, char **argv, char **envp)
{
	t_node	*tokens;
	t_cmd	*cmds;
	char	*str;
	char	**env;
	char	prompt[100];
	int 	exit_code;

	(void)argc;
	(void)argv;
	exit_code = 0;
	env = copy_env(envp); // minisehll a sa propre copie du env pour le modifier (export, unset, etc)
	if (!env)
		return (1);
	while (1)
	{
		setup_signals_interactive();
		// On active les signaux du mode interactif AVANT readline pour que ctrl-C affiche un nouveau propmpt
		build_prompt(prompt);
		str = readline(prompt);
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
				expand_cmds(cmds, exit_code, env);
				exit_code = exec(cmds, env);
				// display_cmds(cmds);
				free_cmds(&cmds);
			}
			clean_struct(&tokens);
		}
		free(str);
	}
}
