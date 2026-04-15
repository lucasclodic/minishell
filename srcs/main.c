/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclodic <lclodic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 17:08:58 by lucas             #+#    #+#             */
/*   Updated: 2026/04/15 19:44:00 by lclodic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	build_prompt(char *buf)
{
	char	*cwd;
	size_t	len;
	size_t	i;
	char	*ms;

	len = 0;
	i = 0;
	ms = " $ minishell> ";
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		while (cwd[i] && len < 80)
			buf[len++] = cwd[i++];
		free(cwd);
	}
	i = 0;
	while (ms[i] && len < 99)
		buf[len++] = ms[i++];
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
	t_data	ctx;

	*should_break = 0;
	tokens = tokeniser(str);
	if (!tokens)
	{
		if (has_content(str))
			return (2);
		return (exit_code);
	}
	cmds = parser(tokens);
	if (!cmds)
		return (clean_struct(&tokens), exit_code);
	ctx.str_ref = str;
	ctx.tokens_ref = tokens;
	exit_code = run_cmds(cmds, env, exit_code, &ctx);
	free_cmds(&cmds);
	clean_struct(&tokens);
	if (!isatty(STDIN_FILENO) && exit_code == 130)
		return (write(1, "\n", 1), *should_break = 1, exit_code);
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
