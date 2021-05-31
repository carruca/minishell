#include "../minishell.h"

char	*get_env_name(char *str, int *i)
{
	char	*envp;
	int		envc;
	int		j;

	j = *i;
	envc = 0;
	if(str[*i] == '?')
	{
		(*i)++;
		envc++;
	}
	else
	{
		while (!ft_strchr(" $\'\"\0", str[*i]))
		{
			(*i)++;
			envc++;
		}
	}
	envp = malloc(sizeof(char) *envc + 1);
	if (!envp)
		return (NULL);
	ft_strlcpy(envp, str + j, envc + 1);
	return (envp);
}
