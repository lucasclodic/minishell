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
