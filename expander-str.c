/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander-str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 10:50:11 by lucas             #+#    #+#             */
/*   Updated: 2026/03/20 10:50:13 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	copy_var(char *result, int *j, char *str, int *i, int es)
{
	char	*val;
	int		k;

	val = get_var_value(str, i, es);
	if (!val)
		return ;
	k = 0;
	while (val[k])
	{
		result[*j] = val[k];
		(*j)++;
		k++;
	}
	free(val);
}

static void	expand_char(char *str, char *res, t_expand *e, int es)
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
		copy_var(res, &e->j, str, &e->i, es);
	else
		res[e->j++] = str[e->i++];
}

char	*expand_str(char *str, int exit_status)
{
	char		*result;
	t_expand	e;

	result = malloc(sizeof(char) * (expanded_len(str, exit_status) + 1));
	if (!result)
		return (NULL);
	e.i = 0;
	e.j = 0;
	e.quote = 0;
	while (str[e.i])
		expand_char(str, result, &e, exit_status);
	result[e.j] = '\0';
	return (result);
}
