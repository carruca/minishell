#include "../minishell.h"

void	copy_expander(char *dst, char *src, t_pos *pos, t_shell *sh)
{
	char	*envp;

	pos->i++;
	envp = get_env_name(src, &pos->i);
	copy_env(dst, envp, &pos->j, sh);
	free(envp);
}
