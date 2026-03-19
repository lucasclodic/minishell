/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer-utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 17:08:45 by lucas             #+#    #+#             */
/*   Updated: 2026/03/19 17:08:46 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void clean_struct(t_node **first)
{
	t_node *temp;
	t_node *current;

	if (!*first)
		return ;
	current = *first;
	while (current->next)
	{
		temp = current->next;
		free(current->str);
		free(current);
		current = temp;
	}
	free(current->str);
	free(current);
	*first = NULL;
}

int is_not_space_or_operator(char c)
{
	return (c == ' ' || c == '\t' || c == '|' || c == '<' || c == '>');
}

t_token_type token_type_identifier(char *str, int start, int end)
{
	if (str[start] == '|')
		return (PIPE);
	if (str[start] == '<' && str[start + 1] && str[start + 1] == '<')
		return (HEREDOC);
	if (str[start] == '>' && str[start + 1] && str[start + 1] == '>')
		return (APPEND);
	if (str[start] == '<')
		return (REDIR_IN);
	if (str[start] == '>')
		return (REDIR_OUT);
	return (WORD);
}

int skip_word(char *str, int i)
{
	int type;

	while (str[i] && !is_not_space_or_operator(str[i]))
	{
		if (str[i] == 34 || str[i] == 39) // 34 pour " et 39 pour '
		{
			type = str[i]; 
			i++;
			while (str[i] && str[i] != type)
				i++;
			if (!str[i])
                return (-1);
			i++;
		}
		else
			i++; 
	}
	return (i);
}

t_node *create_node(char * str, int start, int end)
{
	t_node *output; 

	output = malloc(sizeof(t_node) * 1); 
	if (!output)
		return (NULL);
	output->str = ft_substr(str, start, end);
	if (!output->str)
	{
		free(output);
		return (NULL);
	}
	output->type = token_type_identifier(str, start, end);
	output->next = NULL; 
	return (output);
}