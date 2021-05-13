#include "minishell.h"

void	print_echo(char **cmd)
{
	int	check;

	check = 1;
	while (*cmd && !ft_strcmp(*cmd, "-n"))
	{
		check = 0;
		cmd++;
	}
	if (*cmd)
		ft_putstr_fd(*cmd, 1);
	while (*cmd && *(++cmd))
	{
		ft_putstr_fd(" ", 1);
		ft_putstr_fd(*cmd, 1);
	}
	if (check)
		ft_putstr_fd("\n", 1);
}

int	execute_builtin(int argc, char **cmdline, t_env *_env)
{
	char	cwd[2048];

	if (*cmdline)
	{
		if (!ft_strcmp(*cmdline, "pwd"))
		{
			getcwd(cwd, sizeof(cwd));
			printf("%s\n", cwd);
			return (1);
		}
		else if (!ft_strcmp(*cmdline, "env"))
			return(imprimir_tabla(var_to_array(_env->env_lst)));
		else if (!ft_strcmp(*cmdline, "export"))
			return(set_export(argc, cmdline, _env));
		else if (!ft_strcmp(*cmdline, "unset"))
			return(ft_delete_node(_env->env_lst, &*(++cmdline)));
		else if (!ft_strcmp(*cmdline, "echo"))
		{
			cmdline++;
			print_echo(cmdline);
			return (1);
		}
	}
	return (0);
}
