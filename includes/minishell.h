/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnicolas <mnicolas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 17:09:02 by lucas             #+#    #+#             */
/*   Updated: 2026/04/01 15:43:48 by mnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>

// ======== libft ========
# include "../libft/libft.h"

typedef enum e_token_type
{
	WORD,
	PIPE, // |
	REDIR_IN, // <
	REDIR_OUT, // >
	HEREDOC, // << lis l'entrée ligne par ligne jusqu'à ce que tu tombes sur un delimiteur
	APPEND // >> comme > mais n'écrase pas le contenu du fichier
}   t_token_type;

typedef struct s_node
{
	char			*str;
	t_token_type	type;
	struct s_node	*next;
} t_node;

typedef struct s_cmd
{
	char			**args;
	t_node			*redirs;
	struct s_cmd	*next;
} t_cmd;

typedef struct s_expand
{
	int		i;
	int		j;
	int		quote;
	int		exit_status;
	char	**env;
} t_expand;

// ======== cmd-utils.c ========
t_node	*create_redir(t_token_type type, char *filename);
void	free_args(char **args, int count);
void	free_cmds(t_cmd **cmds);

// ======== cmd.c ========
t_cmd	*parser(t_node *tokens);

// ======== expander-str.c ========
char	*expand_str(char *str, t_expand *e);

// ======== expander.c ========
int		expand_cmds(t_cmd *cmds, int exit_status, char **env);

// ======== expander-utils.c ========
char	*get_var_value(char *str, int *i, t_expand *e);
int		expanded_len(char *str, t_expand *e);
void	free_args(char **args, int count);

// ======== minishell.c ========
char	*get_env(char **env, char *name);

// ======== tokeniser-utils.c ========
void	clean_struct(t_node **first);
int		skip_word(char *str, int i);
t_node	*create_node(char *str, int start, int end);

// ======== tokeniser.c ========
void	add_node_to_main(t_node **head, t_node *node);
t_node	*tokeniser(char *str);

// ======== get-env.c ========
char	*get_env(char **env, char *name);
int		set_env(char ***env, char *name, char *value);
void	remove_env(char ***env, char *name);
char	**copy_env(char **envp);

// ======== builtins/builtins.c ========
int		is_builtin(char *cmd);
int		exec_builtin(t_cmd *cmd, char ***env);

// ======== signals/signals.c ========
extern volatile	sig_atomic_t	g_signal;
void	setup_signals_interactive(void);
void	setup_signals_default(void);
void	setup_signals_ignore(void);

// ======== builtins ========
int		ft_echo(char **args);
int		ft_cd(char **args, char ***env);
int		ft_pwd(void);
int		ft_export(char **args, char ***env);
int		ft_unset(char **args, char ***env);
int		ft_env(char **env);
int		ft_exit(char **args);

// ======== error.c ========
void	syntax_error(char *token);
void	print_error(char *cmd, char *arg, char *msg);

// ======== exec ========
typedef struct s_data
{
	int		cmd_count;
	int		infd;
	int		outfd;
	int		pipefd[2];
	int		i;
	pid_t	*pid;
	int 	here_doc;
	int		open_code;
	int		data_code;
	int		here_doc_code;
}	t_data;

void	*free_words(char **words);
int		free_perror_return(char *str);
void	work_child(t_cmd *cmd, char **envp, t_data data);
int		wait_and_return(t_data data);
int		fork_child(t_cmd *cmd, t_data *data, char **envp);
void	cmd_not_found(char *str);
void	free_and_exit(t_cmd *cmd, int exit_code);
void	execute(t_cmd *cmds, char **envp, t_data data);
void	free_perror_exit(char *str, t_data data);
int		exec(t_cmd *cmds, char **envp);
int 	open_redirs_in(t_node *redirs, t_data *data);
int		open_redirs_out(t_node *redirs, t_data *data);
int		ft_strcmp(const char *s1, const char *s2);
int		get_lines(char *delim, t_data *data);
int		count_cmds(t_cmd *cmds);
int 	free_pid_return(int code, pid_t *pid);
int		open_and_error(t_data *data, t_cmd *cmd);
int		init_data(t_data *data, t_cmd *cmd);
void	close_backup_and_return(int stdin_backup, int stdout_backup, char *str);
void	close_in_out(int infd, int outfd);
void	execve_err_msg(char *cmd, int mode);

#endif