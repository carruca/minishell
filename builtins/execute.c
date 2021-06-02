#include "../minishell.h"

int	execute_builtin(t_shell *sh, t_exec *exec)
{
	if (exec->argc > 0)
	{
		if (exec->builtin == EXPORT_BUILTIN)
			builtin_export(sh, exec->argc, exec->argv);
		else if (exec->builtin == ENV_BUILTIN)
			builtin_env(sh->env_lst);
		else if (exec->builtin == EXIT_BUILTIN)
			builtin_exit(sh, exec->argc, exec->argv);
		else if (exec->builtin == CD_BUILTIN)
			builtin_cd(sh, exec->argc, exec->argv);
		else if (exec->builtin == PWD_BUILTIN)
			builtin_pwd(sh);
		else if (exec->builtin == UNSET_BUILTIN)
			builtin_unset(sh, exec->argc, exec->argv);
		else if (exec->builtin == ECHO_BUILTIN)
			builtin_echo(sh, &exec->argv[1]);
	}
	return (0);
}

