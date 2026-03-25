/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander-utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 10:31:27 by lucas             #+#    #+#             */
/*   Updated: 2026/03/23 18:56:11 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_var_char(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9') || c == '_');
}

static char	*get_env_value(char *str, int *i, char **env)
{
	int		start;
	char	*name;
	char	*value;

	start = *i;
	while (str[*i] && is_var_char(str[*i]))
		(*i)++;
	name = ft_substr(str, start, *i);
	if (!name)
		return (NULL);
	value = get_env(env, name);
	free(name);
	if (value)
		return (ft_strdup(value));
	return (ft_strdup(""));
}

char	*get_var_value(char *str, int *i, t_expand *e)
{
	(*i)++;
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(e->exit_status));
	}
	if (!is_var_char(str[*i]))
		return (ft_strdup("$"));
	if (str[*i] >= '0' && str[*i] <= '9')
	{
		(*i)++;
		return (ft_strdup(""));
	}
	return (get_env_value(str, i, e->env));
}

static void	len_char(char *str, int *i, int *len, t_expand *e)
{
	char	*val;

	if ((str[*i] == '\'' || str[*i] == '"') && e->quote == 0)
		e->quote = str[(*i)++];
	else if (str[*i] == e->quote)
	{
		e->quote = 0;
		(*i)++;
	}
	else if (str[*i] == '$' && e->quote != '\'' && str[*i + 1]
		&& str[*i + 1] != ' ' && str[*i + 1] != '"'
		&& str[*i + 1] != '\'')
	{
		val = get_var_value(str, i, e);
		if (val)
		{
			*len += ft_strlen(val);
			free(val);
		}
	}
	else
	{
		(*len)++;
		(*i)++;
	}
}

int	expanded_len(char *str, t_expand *e)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	e->quote = 0;
	while (str[i])
		len_char(str, &i, &len, e);
	return (len);
}
