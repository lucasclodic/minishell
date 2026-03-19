/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 17:09:02 by lucas             #+#    #+#             */
/*   Updated: 2026/03/19 17:09:03 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>

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

// ======== parser-utils.c ========
t_node	*create_redir(t_token_type type, char *filename);
void	free_args(char **args, int count);
void	free_cmds(t_cmd **cmds);

// ======== parser.c ========
t_cmd	*parser(t_node *tokens);

// ======== libft.c  (temp) ========
int		ft_strlen(char *str);
char	*ft_strdup(char *str);
char	*ft_substr(char *str, int start, int end);

// ======== lexer-utils.c ========
void    clean_struct(t_node **first);
int     is_not_space_or_operator(char c);
t_token_type    token_type_identifier(char *str, int start, int end);
int skip_word(char *str, int i);
t_node *create_node(char * str, int start, int end);

// ======== lexer.c ========
void add_node_to_main(t_node **head, t_node *node);
int handle_operator(char *str, int i, t_node **head);
int handle_word(char *str, int i, t_node **head);
t_node * tokeniser(char *str);

#endif