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

int	cmp_value_var(t_var *var, char *value)
{
	if (!ft_strcmp(var->value, value))
		return (1);
	return (0);
}

t_lista	*ft_lstfind_double(t_lista *lst, void *content, int (*cmp)())
{
	if (lst && cmp)
	{
		while (lst)
		{
			if (!cmp(content, lst->content))
				return (lst);
			lst = lst->next;
		}
	}
	return (NULL);
}

t_lista	*ft_lstnew_double(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = (void *)content;
	new->next = NULL;
	return (new);
}

t_lista	*ft_lstlast_double(t_lista *lst)
{
	if (lst)
		while (lst->next)
			lst = lst->next;
	return (lst);
}


int	set_env_2(t_lista *lst, char *name, char *value, int overwrite)
{
	t_lista	
	t_var	*var;
	char	*ptr;

	var = ft_lstfind_double(lst, &cmp_value_var);
	if (!var)
	{
		lst = ft_lstlast_double(lst);
		lst->next = ft_lstnew()
	}
	
/*	while (lst)
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
	}*/
	return (0);
}

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
			set_env_2(sh->_env.env_lst, "PWD",
					getcwd(pwd, sizeof(char) * 2048), 1);
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
