/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 17:09:02 by lucas             #+#    #+#             */
/*   Updated: 2026/03/24 12:26:48 by lucas            ###   ########.fr       */
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

// ======== libft.c  (temp) ========
int		ft_strlen(char *str);
char	*ft_strdup(char *str);
char	*ft_itoa(int n);
char	*ft_substr(char *str, int start, int end);
int		ft_strncmp(char *s1, char *s2, int n);
int		ft_strchr(char *str, char c);

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
extern int	g_signal;
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

#endif