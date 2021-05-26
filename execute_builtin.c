#include "minishell.h"

int	_echo(t_shell *sh, char **argv)
{
	int	newline_char;

	newline_char = 1;
	while (*argv && !ft_strcmp(*argv, "-n"))
	{
		newline_char = 0;
		argv++;
	}
	if (*argv)
		ft_putstr_fd(*argv, 1);
	while (*argv && *(++argv))
	{
		ft_putstr_fd(" ", 1);
		ft_putstr_fd(*argv, 1);
	}
	if (newline_char)
		ft_putstr_fd("\n", 1);
	sh->status = 0;
	return (1);
}

int	execute_builtin(int argc, char **cmdline, t_cap *cap)
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
			return(imprimir_tabla(var_to_array(cap->env_lst)));
		else if (!ft_strcmp(*cmdline, "export"))
			return(set_export(argc, cmdline, cap));
		else if (!ft_strcmp(*cmdline, "unset"))
			return(ft_delete_node(cap->env_lst, &*(++cmdline)));
		else if (!ft_strcmp(*cmdline, "echo"))
		{
			cmdline++;
//			print_echo(cmdline);
			return (1);
		}
	}
	return (0);
}
