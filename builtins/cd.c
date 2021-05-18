/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 14:24:02 by tsierra-          #+#    #+#             */
/*   Updated: 2021/05/18 22:37:04 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_cd(t_shell *sh, int	argc, char **argv)
{
	int		ret;
	char	*dir;
	char	pwd[2048];
	char	*oldpwd;

	if (argc == 1)
		dir = find_node("HOME", sh->_env.env_lst);
	else
		dir = argv[1];
	ret = chdir(dir);
	if (!dir)
		print_builtin_error(sh, argv, "HOME not set", 1);
	else if (ret < 0)
		print_builtin_error(sh, argv, strerror(errno), 1);
	else
	{
		oldpwd = find_node("PWD", sh->_env.env_lst);
		if (oldpwd)
		{
			set_env(sh->_env.env_lst, "PWD",
					getcwd(pwd, sizeof(char) * 2048));
			if (find_node("OLDPWD", sh->_env.env_lst) != NULL)
			{
				oldpwd = ft_strdup(oldpwd);
				set_env(sh->_env.env_lst, "OLDPWD", oldpwd);
			}
		}
		sh->status = 0;
	}
	return (1);
}
