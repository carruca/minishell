#include "../minishell.h"

int	count_expander(char *str, int *i, int *counter, t_shell *sh)
{
	char	*envp;
	int		env_len;

	(*i)++;
	envp = get_env_name(str, i);
	env_len = count_env(envp, sh);
	*counter += env_len;
	free(envp);
	return (env_len);
}
