#include "minishell.h"

static void	copy_var(char *result, int *j, char *str, int *i, int exit_status)
{
	char	*val;
	int		k;

	val = get_var_value(str, i, exit_status);
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

static char	*expand_str(char *str, int exit_status)
{
	char	*result;
	int		i;
	int		j;
	int		quote;

	result = malloc(sizeof(char) * (expanded_len(str, exit_status) + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
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
			copy_var(result, &j, str, &i, exit_status);
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

static int	expand_args(t_cmd *cmd, int exit_status)
{
	int		i;
	char	*expanded;

	i = 0;
	while (cmd->args[i])
	{
		expanded = expand_str(cmd->args[i], exit_status);
		if (!expanded)
			return (0);
		free(cmd->args[i]);
		cmd->args[i] = expanded;
		i++;
	}
	return (1);
}

static int	expand_redirs(t_cmd *cmd, int exit_status)
{
	t_node	*redir;
	char	*expanded;

	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type != HEREDOC)
		{
			expanded = expand_str(redir->str, exit_status);
			if (!expanded)
				return (0);
			free(redir->str);
			redir->str = expanded;
		}
		redir = redir->next;
	}
	return (1);
}

int	expand_cmds(t_cmd *cmds, int exit_status)
{
	while (cmds)
	{
		if (!expand_args(cmds, exit_status))
			return (0);
		if (!expand_redirs(cmds, exit_status))
			return (0);
		cmds = cmds->next;
	}
	return (1);
}
