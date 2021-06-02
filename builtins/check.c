/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:58:28 by tsierra-          #+#    #+#             */
/*   Updated: 2021/05/28 20:00:42 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_builtin(int argc, char *arg)
{
	if (argc > 0)
	{
		if (!ft_strcmp(arg, "cd"))
			return (CD_BUILTIN);
		else if (!ft_strcmp(arg, "exit"))
			return (EXIT_BUILTIN);
		else if (!ft_strcmp(arg, "pwd"))
			return (PWD_BUILTIN);
		else if (!ft_strcmp(arg, "env"))
			return (ENV_BUILTIN);
		else if (!ft_strcmp(arg, "export"))
			return (EXPORT_BUILTIN);
		else if (!ft_strcmp(arg, "unset"))
			return (UNSET_BUILTIN);
		else if (!ft_strcmp(arg, "echo"))
			return (ECHO_BUILTIN);
	}
	return (0);
}
/*
int	check_builtini2(t_shell *sh, int argc, char **argv)
{
	if (argc > 0)
	{
		if (!ft_strcmp(argv[0], "cd"))
			return (builtin_cd(sh, argc, argv));
		else if (!ft_strcmp(argv[0], "exit"))
			return (builtin_exit(sh, argc, argv));
		else if (!ft_strcmp(argv[0], "pwd"))
			return (builtin_pwd(sh));
		else if (!ft_strcmp(argv[0], "env"))
			return (builtin_env(sh->env_lst));
		else if (!ft_strcmp(argv[0], "export"))
			return (builtin_export(sh, argc, argv));
		else if (!ft_strcmp(argv[0], "unset"))
			return (builtin_unset(sh, argc, argv));
		else if (!ft_strcmp(argv[0], "echo"))
			return (builtin_echo(sh, &argv[1]));
	}
	return (0);
}*/
