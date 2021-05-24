/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 14:24:02 by tsierra-          #+#    #+#             */
/*   Updated: 2021/05/19 16:39:21 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cmp_value_var(char *value, t_var *var)
{
	if (!ft_strcmp(var->value, value))
		return (1);
	return (0);
}
/*
int	set_env_2(t_lista *lst, char *name, char *value, int overwrite)
{
	t_list	*lst;
	t_var	*var;
	char	*ptr;

	lst = ft_lstfind(lst, value, &cmp_value_var);
	if (!var)
	{
		var = ft_lstnew();
		ft_lst
	}
	
	while (lst)
	{
		var = lst->content;
		if (!ft_strcmp(name, var->name) && overwrite)
		{
			ptr	= var->value;
			var->value = ft_strdup(value);
			free(ptr);
			return (1);
		}
		lst = lst->next;
	}
	return (0);
}*/

int	builtin_cd(t_shell *sh, int	argc, char **argv)
{
	int		ret;
	char	*dir;
//	char	pwd[2048];
	char	*oldpwd;

	if (argc == 1)
		dir = get_env_value("HOME", sh->env_lst);
	else
		dir = argv[1];
	if (!dir)
		print_builtin_error(sh, argv, "HOME not set", 1);
	ret = chdir(dir);
	if (ret < 0)
		print_builtin_error(sh, argv, strerror(errno), 1);
	else
	{
		oldpwd = get_env_value("PWD", sh->env_lst);
		if (oldpwd)
		{
/*			set_env_2(sh->_env.env_lst, "PWD",
					getcwd(pwd, sizeof(char) * 2048), 1);*/
		/*	if (find_node("OLDPWD", sh->_env.env_lst) != NULL)
			{
			//	oldpwd = ft_strdup(oldpwd);
				set_env(sh->_env.env_lst, "OLDPWD", oldpwd);
			}*/
		}
		sh->status = 0;
	}
	return (1);
}
