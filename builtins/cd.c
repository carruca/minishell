/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 14:24:02 by tsierra-          #+#    #+#             */
/*   Updated: 2021/05/28 20:11:48 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	change_directory(t_shell *sh, char **argv, char *dir)
{
	int		ret;
	char	pwd[2048];
	char	*oldpwd;

	if (!dir)
		dir = argv[1];
	ret = chdir(dir);
	if (ret < 0)
		print_builtin_error(sh, argv, strerror(errno), 1);
	else
	{
		oldpwd = get_env_value("PWD", sh->env_lst);
		if (oldpwd)
		{
			set_var2("OLDPWD", oldpwd, &sh->env_lst, modify_value2);
			set_var2("PWD", getcwd(pwd, sizeof(char) * 2048),
				&sh->env_lst, modify_value2);
		}
		sh->status = 0;
	}
	return (1);
}

int	builtin_cd(t_shell *sh, int argc, char **argv)
{
	char	*dir;

	dir = NULL;
	if (argc == 1)
	{
		dir = get_env_value("HOME", sh->env_lst);
		if (!dir)
		{
			print_builtin_error(sh, argv, "HOME not set", 1);
			return (1);
		}
	}
	else if (!ft_strcmp(argv[1], "-"))
	{
		dir = get_env_value("OLDPWD", sh->env_lst);
		if (!dir)
		{
			print_builtin_error(sh, argv, "OLDPWD not set", 1);
			return (1);
		}
	}
	return (change_directory(sh, argv, dir));
}
