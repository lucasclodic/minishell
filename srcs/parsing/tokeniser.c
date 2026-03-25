/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 17:08:49 by lucas             #+#    #+#             */
/*   Updated: 2026/03/23 18:13:11 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void add_node_to_main(t_node **head, t_node *node)
{
	t_node *tmp; 

	if (!node)
		return ;
	if (!*head)
		*head = node; 
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
}

static int	handle_operator(char *str, int i, t_node **head)
{
	t_node *new; 
	int end;

	if (str[i] != '|' && str[i + 1] && str[i] == str[i + 1])
		end = i + 2;
	else
		end = i + 1;
	new = create_node(str, i, end);
	if (!new)
	{
		clean_struct(head);
		return (-1);
	}
	add_node_to_main(head, new);
	return (end);
}

static int	handle_word(char *str, int i, t_node **head)
{
	t_node *new;
	int end;

	end = skip_word(str, i);
	if (end == -1)
	{
		printf("minishell: syntax error unclosed apostrophes\n");
		clean_struct(head);
		return (-1);
	}
	new = create_node(str, i, end);
	if (!new)
	{
		clean_struct(head);
		return (-1);
	}
	add_node_to_main(head, new);
	return (end);
}

int check_syntax(t_node *head)
{
	t_node *prec; 

	prec = NULL;
	while (head)
	{
		if (head->type == PIPE && !(prec && prec->type == WORD && head->next))
		{
			printf("minishell: syntax error near unexpected token '%s'\n", head->str);
			return (0);
		}
		if ((head->type == REDIR_IN || head->type == REDIR_OUT || head->type == APPEND || head->type == HEREDOC)
			&& !(head->next && head->next->type == WORD))
		{
			if (head->next)
				printf("minishell: syntax error near unexpected token '%s'\n", head->next->str);
			else
				printf("minishell: syntax error near unexpected token '\\n'\n");
			return (0);
		}
		prec = head; 
		head = head->next; 
	}
	return (1);
}

t_node * tokeniser(char *str)
{
	int i; 
	t_node *HEAD;

	i = 0; 
	HEAD = NULL;
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++; 
		if (!str[i])
			break ;
		if (str[i] == '|' || str[i] == '<' || str[i] == '>')
			i = handle_operator(str, i, &HEAD);
		else
			i = handle_word(str, i, &HEAD);
		if (i == -1)
			return (NULL);
	}
	if (!check_syntax(HEAD))
	{
		clean_struct(&HEAD);
		return (NULL);
	}
	return (HEAD);
}

