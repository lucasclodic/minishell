/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnicolas <mnicolas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 17:08:58 by lucas             #+#    #+#             */
/*   Updated: 2026/04/15 15:16:40 by mnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	env = copy_env(envp);
	if (!env)
		return (1);
	while (1)
	{
		setup_signals_interactive();
		build_prompt(prompt);
		if (isatty(STDIN_FILENO))
			str = readline(prompt);
		else
		{
			// str = readline("abcdefghij");
			str = get_next_line(0);
			if (str)
			{
				int len = ft_strlen(str);
				if (len > 0 && str[len - 1] == '\n')
					str[len - 1] = '\0';
			}
		}
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
		if (isatty(STDIN_FILENO))
			add_history(str);
		tokens = tokeniser(str);
		if (tokens)
		{
			cmds = parser(tokens);
			if (cmds)
			{
				expand_cmds(cmds, exit_code, env);
				exit_code = exec(cmds, env);
				if (!isatty(STDIN_FILENO) && exit_code == 130)
				{
					free_cmds(&cmds);
					clean_struct(&tokens);
					free(str);
					write(1, "\n", 1);
					break;
				}
				// display_cmds(cmds);
				free_cmds(&cmds);
			}
			clean_struct(&tokens);
		}
		free(str);
	}
	if (isatty(STDIN_FILENO))
		rl_clear_history();
	return (exit_code);
}
