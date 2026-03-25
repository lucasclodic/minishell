/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander-str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 10:50:11 by lucas             #+#    #+#             */
/*   Updated: 2026/03/23 18:55:36 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	copy_var(char *result, char *str, t_expand *e)
{
	char	*val;
	int		k;

	val = get_var_value(str, &e->i, e);
	if (!val)
		return ;
	k = 0;
	while (val[k])
	{
		result[e->j] = val[k];
		e->j++;
		k++;
	}
	free(val);
}

static void	expand_char(char *str, char *res, t_expand *e)
{
	if ((str[e->i] == '\'' || str[e->i] == '"') && e->quote == 0)
		e->quote = str[e->i++];
	else if (str[e->i] == e->quote)
	{
		e->quote = 0;
		e->i++;
	}
	else if (str[e->i] == '$' && e->quote != '\'' && str[e->i + 1]
		&& str[e->i + 1] != ' ' && str[e->i + 1] != '"'
		&& str[e->i + 1] != '\'')
		copy_var(res, str, e);
	else
		res[e->j++] = str[e->i++];
}

char	*expand_str(char *str, t_expand *e)
{
	char	*result;

	result = malloc(sizeof(char) * (expanded_len(str, e) + 1));
	if (!result)
		return (NULL);
	e->i = 0;
	e->j = 0;
	e->quote = 0;
	while (str[e->i])
		expand_char(str, result, e);
	result[e->j] = '\0';
	return (result);
}
