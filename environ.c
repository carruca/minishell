/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 16:23:43 by tsierra-          #+#    #+#             */
/*   Updated: 2021/05/21 16:47:22 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		return (1);
	}
	*name = ft_substr(env, 0, pos - env);
	if (!*name)
		return (0);
	*value = ft_strdup(pos + 1);
	if (!*value)
		return (0);
	return (1);
}

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

void	set_flag(t_var *var, int flags)
{
	var->flags |= flags;
}

void	unset_flag(t_var *var, int flags)
{
	var->flags ^= flags;
}

static int	env_name_cmp(char *name, t_var *var)
{
	return (ft_strcmp(name, var->name) == 0);
}

char	*up_shlvl(t_shell *sh, char *value)
{
	t_var	*var;
	char	*new;
	int		tmp;
	
//var = get_var_by_name(sh->env_lst, "SHLVL", ENV_VAR | EXPORT_VAR, CREATE);

//	var = ft_lstfind(sh->env_lst, "SHLVL", env_name_cmp);
	if (!var)
				
	if (!value || !*value)
		tmp = 0;
	else
		tmp = ft_atoi(value);
	new = ft_itoa(++tmp);
	if (!new)
		return (NULL);
	return (new);
}

char	*capture_value(char *env, char *name)
{
	char	*value;
	char	*tmp;

	tmp = ft_strchr(env, '=');
	if (!tmp)
		return (ft_strdup(""));
	if (!ft_strcmp(name, "SHLVL"))
		value = up_shlvl(tmp + 1);
	else
		value = ft_strdup(tmp + 1);
	if (!value)
		return (NULL);
	return (value);
}

int		capture_flags(char *str, char *name)
{
	if (!ft_strcmp(name, "_"))
		return (ENV_VAR);
	else if (!ft_strchr(str, '='))
		return (EXPORT_VAR);
	return (EXPORT_VAR | ENV_VAR);
}

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
	flags = capture_flags(str, name);
	var = create_var(name, value, flags);
	if (!var)
	{
		free(name);
		free(value);
		return (NULL);
	}
	return (var);
}

void	free_var(void *var)
{
	t_var	*tmp;

	tmp = var;
	free(tmp->name);
	free(tmp->value);
	free(tmp);
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
	printf("%s=%s 0x%04x\n", var->name, var->value, var->flags);
}

char	*get_env(char *name, t_list *var_lst)
{
	t_var	*var;

	while (var_lst)
	{
		var = var_lst->content;
		if (!ft_strcmp(name, var->name))
			return (var->value);
		var_lst = var_lst->next;
	}
	return (NULL);
}

int		cmp_var(t_var *var1, t_var *var2)
{
	return (ft_strcmp(var1->name, var2->name));
}

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
}
