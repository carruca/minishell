#include "../minishell.h"

void	restore_env(char **env)
{
	char	*pos;

	pos = ft_strchr(*env, '\0');
	*pos = '=';
}
