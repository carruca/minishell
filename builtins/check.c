/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:58:28 by tsierra-          #+#    #+#             */
/*   Updated: 2021/05/21 16:45:23 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_pwd(t_shell *sh)
{
	char	pwd[2048];

	if (getcwd(pwd, sizeof(char) * 2048))
	{
		ft_putstr_fd(pwd, 1);
		ft_putstr_fd("\n", 1);
		sh->status = 0;
	}
	return (1);
}

int	builtin_env(t_list *var_lst)
{
	t_var	*var;

	while (var_lst)
	{
		var = var_lst->content;
		if (is_env(var))
			printf("%s=%s\n", var->name, var->value);
		var_lst = var_lst->next;
	}
	return (1);
}

int	builtin_echo(t_shell *sh, char **argv)
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

/*
void	ft_sort_tab(char **tab_ptr)
{
	char	*aux;
	char	**ptr;

	while (*tab_ptr)
	{
		ptr = tab_ptr;
		ptr++;
		while (*ptr)
		{
			if (**tab_ptr > **ptr)
			{
				aux = *tab_ptr;
				*tab_ptr = *ptr;
				*ptr = aux;
			}
			else
				ptr++;
		}
		tab_ptr++;
	}
}*/

void	print_identifier_error(t_shell *sh, char *cmd, char *arg, int status)
{
	ft_putstr_fd(sh->prompt, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("not a valid identifier", 2);
	ft_putstr_fd("\n", 2);
	sh->status = status;
}

int	is_valid_identifier(char *str)
{
	while (*str && *str != '=')
	{
		if (ft_isdigit(str[0]) || (!ft_isalnum(*str) && *str != '_'))
			return (0);
		str++;
	}
	return (1);
}

int	builtin_unset(t_shell *sh, int argc, char **argv)
{
	int	i;

	sh->status = 0;
	if (argc > 1)
	{
		i = 1;
		while (argv[i])
		{
			if (!is_valid_identifier(argv[i]))
				print_identifier_error(sh, argv[0], argv[i], 1);
			else
		//		set_env_delete(sh->_env.env_lst, argv[i]);
			i++;
		}
	}
	return (1);
}

void	print_export_var(void *content)
{
	t_var	*var;

	var = content;
	if (var->flags & EXPORT_VAR)
	{
		if (var->value[0])
			printf("declare -x %s=\"%s\"\n", var->name, var->value);
		else
			printf("declare -x %s\n", var->name);
	}
}

static int	print_export(t_list *var_lst)
{
	t_list	*export_lst;

	export_lst = ft_lstclone(var_lst, free);
	if (!export_lst)
		return (1);
	ft_lstsort(export_lst, cmp_var);
	ft_lstiter(export_lst, print_export_var);
	ft_lstclear(&export_lst, NULL);
	return (0);
}

/*
Si tiene nombre: es exportable.
Si tiene valor: es de entorno.
*/

static int	add_new_var(t_list *var_lst, char *str)
{
	t_list	*new_lst;
	t_var	*var;

	var = capture_var(str);
	if (!var)
		return (1);
	print_var(var);
	new_lst = ft_lstnew(var);
	if (!new_lst)
		return (1);
	ft_lstadd_back(&var_lst, new_lst);
	return (0);
}

int	builtin_export(t_shell *sh, int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc > 1)
	{
		while (--argc)
		{
			if (!is_valid_identifier(argv[i]))
				print_identifier_error(sh, argv[0], argv[i], 1);
			else
				sh->status = add_new_var(sh->env_lst, argv[i]);
			i++;
		}
	}
	else
		sh->status = print_export(sh->env_lst);
	return (1);
}

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

void	print_builtin_error(t_shell *sh, char **argv, char *str, int status)
{
	ft_putstr_fd(sh->prompt, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(argv[0], 2);
	ft_putstr_fd(": ", 2);
	if (argv[1])
	{
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	sh->status = status;
}
