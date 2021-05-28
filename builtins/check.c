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

int	check_builtin(t_shell *sh, int argc, char **argv)
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
}
