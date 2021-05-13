#include "minishell.h"

// recibe un string y busca la palabra echo al principio
// si lo encuentra devuelve 0 de lo contrario devuelve 1
// --> esta función es solo para hacer pruebas

// int	find_builtin(char *cmd, char *builtin)
// {
// 	while (*builtin)
// 	{
// 		if (*cmd++ != *builtin++)
// 			return (1);
// 	}
// 	return (0);
// }

// recibe un string y una lista
// imprime en funcion de si encuetra $ o no

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
			return(imprimir_tabla(var_to_array(_env->lst)));
		else if (!ft_strcmp(*cmdline, "export"))
			return(set_export(argc, cmdline, _env));
		else if (!ft_strcmp(*cmdline, "unset"))
			return(ft_delete_node(_env->lst, &*(++cmdline)));
		else if (!ft_strcmp(*cmdline, "echo"))
		{
			cmdline++;
			print_echo(cmdline);
			return (1);
		}
	}
	return (0);
}
