/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 16:23:43 by tsierra-          #+#    #+#             */
/*   Updated: 2021/05/19 22:10:12 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



t_var	*new_env(char *name, char *value, int flags)
{
	t_var	*var;

	var = malloc(sizeof(t_var));
	if (!var)
		return (NULL);
	var->name = name;
	var->value = value;
	var->flags = flags;
	return (var);
}

char	*capture_name(char *env)
{
	char	*name;
	char	*tmp;

	tmp = ft_strchr(env, '=');
	*tmp = '\0';
	name = ft_strdup(env);
	if (!name)
		return (NULL);
	return (name);
}

t_list	*capture_env(char **env)
{
	t_list	*env_lst;
	t_var	*var;
	char	*name;
	char	*value;

	env_lst = NULL;
	while (*env)
	{
		value = ft_strdup(ft_strchr(*env, '=') + 1);
		name = capture_name(*env);
		if (!ft_strcmp(name, "_"))
			var = new_env(name, value, ONLYENV);
		else
			var = new_env(name, value, EXPORT);
		ft_lstadd_back(&env_lst, ft_lstnew(var));
		env++;
	}
	return (env_lst);
}
