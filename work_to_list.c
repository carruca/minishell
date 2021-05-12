#include "minishell.h"

//funcion para encontrar los comandos
//esta función es solo para hacer pruebas

int	work_to_list(t_env *_env, char *cmd)
{
	char	**cmdline;
	int		len;

	if (cmd)
	{
		len = 0;
		cmdline = ft_split(cmd, ' ');
		while (cmdline[len])
			len++;
		execute_builtin(len, cmdline, _env);
		while (_env->lst && _env->lst->prev != NULL)
			_env->lst = _env->lst->prev;
		ft_free_tab(cmdline);
	}
	return (0);
}
