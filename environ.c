/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 16:23:43 by tsierra-          #+#    #+#             */
/*   Updated: 2021/05/24 21:50:36 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

/*
 * build_var(char *str, t_list **env_lst)
 * extract_var(char *str, char **name, char **value)
 * set_var(char *name, char *value, t_list **env_lst, (void)(*f)())
 */

void	extract_var2(char **str, char **name, char **value)
{
	char	*pos;

	pos = ft_strchr(*str, '=');
	if (!pos)
		*name = *str;
	else
	{
		*pos = '\0';
		*name = *str;
		*value = pos + 1;
	}
}

void	set_flags2(t_var *var)
{
	if (!ft_strcmp(var->name, "_"))
		var->flags |= ENV_VAR;
	else if (!var->value)
		var->flags |= EXPORT_VAR;
	else
		var->flags |= (EXPORT_VAR | ENV_VAR);
}

int	init_var2(char *name, char *value, t_list **env_lst)
{
	t_var	*var;

	var = ft_calloc(1 , sizeof(t_var));
	if (!var)
		return (1);
	var->name = ft_strdup(name);
	if (value != NULL)
		var->value = ft_strdup(value);
	set_flags2(var);
	add_var(var, env_lst);
	if (!var)
		return (1);
	return (0);
}

int	modify_value2(char *value, t_var *var)
{
	char	*str;

	if (!value)
		return (1);
	str = ft_strdup(value);
	free(var->value);
	var->value = str;
	set_flags2(var);
	return (1);
}

int	set_var2(char *name, char *value, t_list **env_lst, int (*f)())
{
	t_list	*lst;	
	
	lst = ft_lstfind(*env_lst, name, env_name_cmp);
	if (!lst)
		init_var2(name, value, env_lst);
	else if (f)
		f(value, lst->content);
	return (1);
}

void	restore_env(char **env)
{
	char	*pos;

	pos = ft_strchr(*env, '\0');
	*pos = '=';

}

int	build_var(char **str, t_list **env_lst, int (*f)())
{
	char	*name;
	char	*value;

	name = NULL;
	value = NULL;
	extract_var2(str, &name, &value);
	set_var2(name, value, env_lst, f);
	restore_env(str);
	return (1);
}

t_var	*create_var(char *name, char *value, int flags)
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

int		extract_var(char *env, char **name, char **value)
{
	char	*pos;

	pos = ft_strchr(env, '=');
	if (!pos)
	{
		*name = ft_strdup(env);
		if (!*name)
			return (0);
		return (1);
	}
	*name = ft_substr(env, 0, pos - env);
	if (!*name)
		return (0);
	*value = ft_strdup(pos + 1);
	if (!*value)
	{
		free(*name);
		return (0);
	}
	return (1);
}
//var = get_var_by_name(sh->env_lst, "SHLVL", ENV_VAR | EXPORT_VAR, CREATE);
/*
char	*capture_name(char *env)
{
	char	*name;
	char	*tmp;

	tmp = ft_strchr(env, '=');
	if (!tmp)
	{
		name = ft_strdup(env);
		return (name);
	}
	name = ft_substr(env, 0, tmp - env);
	if (!name)
		return (NULL);
	return (name);
}
*/


void	set_flag(t_var *var, int flags)
{
	var->flags |= flags;
}

void	unset_flag(t_var *var, int flags)
{
	var->flags ^= flags;
}

int	var_name_cmp(void *str, void *var)
{
	char	*ptr;
	t_var	*tmp;

	ptr = str;
	tmp = var;
	return (ft_strncmp(ptr, tmp->name, ft_strlen(tmp->name)));
}

int	env_name_cmp(void *name, void *var)
{
	char	*tmp_name;
	t_var	*tmp_var;

	tmp_name = name;
	tmp_var = var;
	return (ft_strcmp(tmp_name, tmp_var->name) != 0);
}

int	increase_shlvl2(char *str, t_var *var)
{
	int	tmp;

	(void)str;
	tmp = ft_atoi(var->value);
	free(var->value);
	var->value = ft_itoa(++tmp);
	return (1);
}

void	change_value(char *str, t_var *var)
{
	char	*pos;
	char	*tmp;

	pos = ft_strchr(str, '=');
	if (pos)
	{
		tmp = ft_strdup(pos + 1);
		free(var->value);
		var->value = tmp;
		set_flag(var, ENV_VAR);
	}
}

int	add_new_var(char *str, t_list **env_lst, void (*f)())
{
	t_list	*alst;	
	
	alst = ft_lstfind(*env_lst, str, var_name_cmp);
	if (!alst)
		init_var(str, env_lst);
	else if (f)
		f(str, alst->content);
	return (1);
}

/*
int	unset_var(char *name, t_list **env_lst)
{
	t_list	*alst;


	return (0);
}*/

int	increase_shlvl(t_shell *sh)
{
	t_list	*alst;
	t_var	*var;
	int	tmp;
	
	
	alst = ft_lstfind(sh->env_lst, "SHLVL", env_name_cmp);
	if (!alst)
		init_var("SHLVL=1", &sh->env_lst);
	else
	{
		var = alst->content;
		tmp = ft_atoi(var->value);
		free(var->value);
		var->value = ft_itoa(++tmp);
	}
	return (1);
}
/*
char	*capture_value(char *env, char *name)
{
	char	*value;
	char	*tmp;

	tmp = ft_strchr(env, '=');
	if (!tmp)
		return (NULL);
//	if (!ft_strcmp(name, "SHLVL"))
//		value = up_shlvl(tmp + 1);
	else
		value = ft_strdup(tmp + 1);
	if (!value)
		return (NULL);
	return (value);
}*/


void	extract_flags(char *name, char *value, int *flags)
{
	if (!ft_strcmp(name, "_"))
		*flags |= ENV_VAR;
	else if (!value)
		*flags |= EXPORT_VAR;
	else
		*flags |= (EXPORT_VAR | ENV_VAR);
}
/*
t_var	*capture_var(char *str)
{
	t_var	*var;
	char	*name;
	char	*value;
	int		flags;

	name = capture_name(str);
	if (!name)
		return (NULL);
	value = capture_value(str, name);
	if (!value)
	{
		free(name);
		return (NULL);
	}
//	flags = capture_flags(str, name);
	var = create_var(name, value, flags);
	if (!var)
	{
		free(name);
		free(value);
		return (NULL);
	}
	return (var);
}*/

void	free_var(void *var)
{
	t_var	*tmp;

	tmp = var;
	free(tmp->name);
	if (tmp->value)
		free(tmp->value);
	free(tmp);
	tmp = NULL;
}

int		is_export(t_var *var)
{
	if (var->flags & EXPORT_VAR)
		return (1);
	return (0);
}

int		is_env(t_var *var)
{
	if (var->flags & ENV_VAR)
		return (1);
	return (0);
}

char	*join_var(t_var	*var)
{
	return (ft_strjoin_btwchar(var->name, var->value, '='));
}

void	print_var(void *content)
{
	t_var	*var;

	var = content;
	printf("[%s]=[%s] 0x%04x\n", var->name, var->value, var->flags);
}

t_var	*find_var(const char *name, t_list *env_lst)
{
	return ((t_var *)((ft_lstfind(env_lst, (void *)name, env_name_cmp))->content));
}
/*
int	set_env(const char *name, const char *value, int overwrite, t_list *env_lst)
{
	return (1);
}*/

char	*get_env_value(char *name, t_list *env_lst)
{
	t_list	*lst;

	lst = ft_lstfind(env_lst, name, env_name_cmp);
	if (!lst)
		return (NULL);
	return (((t_var *)(lst->content))->value);
}

/*
char	*get_env_2(char *name, t_list *var_lst)
{
//	t_list	*alst;
//	t_var	*var;
//var = get_var_by_name(sh->env_lst, "SHLVL", ENV_VAR | EXPORT_VAR, CREATE);

//	var = ft_lstfind(sh->env_lst, "SHLVL", env_name_cmp);
//	if (!var)
//		return (NULL);

	alst = ft_lstfind(var_lst, name, env_var_cmp);
	if (!alst)
		(NULL);
	return ((t_var *)(alst->content)->value)
	while (var_lst)
	{
		var = var_lst->content;
		if (!ft_strcmp(name, var->name))
			return (var->value);
		var_lst = var_lst->next;
	}
	return (NULL);
}*/

int		cmp_var(t_var *var1, t_var *var2)
{
	return (ft_strcmp(var1->name, var2->name));
}


int	add_var(t_var *var, t_list **env_lst)
{
	t_list	*new_lst;

	new_lst = ft_lstnew(var);
	if (!new_lst)
		return (0);
	ft_lstadd_back(env_lst, new_lst);
	return (1);
}
/*
Tengo que saber si hay una 
*/

int	init_var(char *str, t_list **env_lst)
{
	t_var	*var;

	var = ft_calloc(1 , sizeof(t_var));
	if (!var)
		return (1);
	extract_var(str, &var->name, &var->value);
	extract_flags(var->name, var->value, &var->flags);
	add_var(var, env_lst);
	if (!var)
		return (1);
	return (0);
}

t_list	*extract_env(char **env)
{
	t_list	*env_lst;
/*	t_var	*var;
	char	*name;
	char	*value;
	int	flags;*/

	env_lst	= NULL;
	while (*env)
	{
		build_var(env, &env_lst, modify_value2);
//		init_var(*env, &env_lst);
/*		name = NULL;
		value = NULL;
		flags = 0;
		if (!extract_var(*env, &name, &value))
			return (NULL);
		extract_flags(name, value, &flags);
		var = create_var(name, value, flags);
		if (!var)
			return (NULL);
		add_var(var, &env_lst);*/
		env++;
	}
	return (env_lst);
}
/*
t_list	*capture_env(char **env)
{
	t_list	*var_lst;
	t_list	*tmp;
	t_var	*var;

	var_lst = NULL;
	while (*env)
	{
		var = capture_var(*env);
		if (!var)
		{
			ft_lstiter(var_lst, free_var);
			return (NULL);
		}
		tmp = ft_lstnew(var);
		if (!tmp)
		{
			ft_lstiter(var_lst, free_var);
			return (NULL);
		}
		ft_lstadd_back(&var_lst, tmp);
		env++;
	}
	return (var_lst);
}*/
