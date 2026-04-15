/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclodic <lclodic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 17:50:00 by lclodic           #+#    #+#             */
/*   Updated: 2026/04/15 17:50:00 by lclodic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	run_cmds(t_cmd *cmds, char ***env, int exit_code, t_data *ctx)
{
	expand_cmds(cmds, exit_code, *env);
	ctx->exit_status = exit_code;
	return (exec(cmds, env, ctx));
}

int	has_content(const char *str)
{
	while (*str)
	{
		if (*str != ' ' && *str != '\t')
			return (1);
		str++;
	}
	return (0);
}

char	*get_next_cmd(char *prompt, int *should_break)
{
	char	*str;

	*should_break = 0;
	setup_signals_interactive();
	build_prompt(prompt);
	str = read_input(prompt);
	if (str)
		return (str);
	if (g_signal)
	{
		g_signal = 0;
		return (NULL);
	}
	if (isatty(STDIN_FILENO))
		printf("exit\n");
	*should_break = 1;
	return (NULL);
}
