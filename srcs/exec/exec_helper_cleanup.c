/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper_cleanup.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclodic <lclodic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 16:50:18 by lclodic           #+#    #+#             */
/*   Updated: 2026/04/15 16:54:15 by lclodic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	child_cleanup_and_exit(t_cmd *cmds, char **env, t_data data, int code)
{
	if (cmds)
		free_cmds(&cmds);
	if (data.tokens_ref)
		clean_struct(&data.tokens_ref);
	if (env)
		free_words(env);
	if (data.str_ref)
		free(data.str_ref);
	if (data.pid)
		free(data.pid);
	rl_clear_history();
	free_gnl_buffer();
	exit(code);
}
