/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclodic <lclodic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 17:08:58 by lucas             #+#    #+#             */
/*   Updated: 2026/04/15 16:48:04 by lclodic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	build_prompt(char *buf)
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

char	*read_input(char *prompt)
{
	char	*str;
	int		len;

	if (isatty(STDIN_FILENO))
		return (readline(prompt));
	str = get_next_line(0);
	if (str)
	{
		len = ft_strlen(str);
		if (len > 0 && str[len - 1] == '\n')
			str[len - 1] = '\0';
	}
	return (str);
}

int	process_line(char *str, char ***env, int exit_code, int *should_break)
{
	t_node	*tokens;
	t_cmd	*cmds;

	*should_break = 0;
	tokens = tokeniser(str);
	if (!tokens)
		return (exit_code);
	cmds = parser(tokens);
	if (!cmds)
		return (clean_struct(&tokens), exit_code);
	expand_cmds(cmds, exit_code, *env);
	exit_code = exec(cmds, env, str, tokens);
	free_cmds(&cmds);
	clean_struct(&tokens);
	if (!isatty(STDIN_FILENO) && exit_code == 130)
	{
		write(1, "\n", 1);
		*should_break = 1;
	}
	return (exit_code);
}

int	run_shell(char ***env)
{
	char	*str;
	char	prompt[100];
	int		exit_code;
	int		should_break;

	exit_code = 0;
	while (1)
	{
		str = get_next_cmd(prompt, &should_break);
		if (!str)
		{
			if (should_break)
				break ;
			continue ;
		}
		if (isatty(STDIN_FILENO))
			add_history(str);
		exit_code = process_line(str, env, exit_code, &should_break);
		free(str);
		if (should_break)
			break ;
	}
	return (exit_code);
}

int	main(int argc, char **argv, char **envp)
{
	char	**env;
	int		exit_code;

	(void)argc;
	(void)argv;
	env = copy_env(envp);
	if (!env)
		return (1);
	exit_code = run_shell(&env);
	if (isatty(STDIN_FILENO))
		rl_clear_history();
	free_words(env);
	free_gnl_buffer();
	return (exit_code);
}
