#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

int is_not_space_or_operator(char c)
{
	return (c == ' ' || c == '\t' || c == '|' || c == '<' || c == '>');
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
			if (str[i])
				i++;
		}
        else
		    i++; 
	}
	return (i);
}

int main(int argc, char **argv, char **envp)
{
    int i; 
    int j;

	while (1)
	{
		char *str = readline("minishell> ");
		if (!str)
			return (1); 
		add_history(str);
        i = 0;
        j = 1;
		while (str[i])
        {
            printf("Token %d : de %d à %d\n", j, i, skip_word(str, i));
            i = skip_word(str, i);
            j++;
        }
		free(str);
	}
	// rl_clear_history();
}