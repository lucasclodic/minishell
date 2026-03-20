#include "minishell.h"

int	is_var_char(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9') || c == '_');
}

char	*get_var_value(char *str, int *i, int exit_status)
{
	int		start;
	char	*name;
	char	*value;

	(*i)++;
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(exit_status));
	}
	if (!is_var_char(str[*i]))
		return (ft_strdup("$"));
	start = *i;
	while (str[*i] && is_var_char(str[*i]))
		(*i)++;
	name = ft_substr(str, start, *i);
	if (!name)
		return (NULL);
	value = getenv(name);
	free(name);
	if (value)
		return (ft_strdup(value));
	return (ft_strdup(""));
}

int	expanded_len(char *str, int exit_status)
{
	int		i;
	int		len;
	int		quote;
	char	*val;

	i = 0;
	len = 0;
	quote = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && quote == 0)
			quote = str[i++];
		else if (str[i] == quote)
		{
			quote = 0;
			i++;
		}
		else if (str[i] == '$' && quote != '\'' && str[i + 1]
			&& str[i + 1] != ' ' && str[i + 1] != '"'
			&& str[i + 1] != '\'')
		{
			val = get_var_value(str, &i, exit_status);
			if (val)
			{
				len += ft_strlen(val);
				free(val);
			}
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}
