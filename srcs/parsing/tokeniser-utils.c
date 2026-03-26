/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser-utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 17:08:45 by lucas             #+#    #+#             */
/*   Updated: 2026/03/26 10:32:48 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static int	is_space_or_operator(char c)
{
	return (c == ' ' || c == '\t' || c == '|' || c == '<' || c == '>'); // retourne 1 si c est un espace
}

static t_token_type	token_type_identifier(char *str, int start)
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

	while (str[i] && !is_space_or_operator(str[i]))
	{
		if (str[i] == '\'' || str[i] == '"')  // si tu tombes sur une quote tu dois avancer jusqu'à trouver la fin, une quote non fermée est une erreur 
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
	output->type = token_type_identifier(str, start);
	output->next = NULL; 
	return (output);
}