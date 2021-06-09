/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 19:58:20 by tsierra-          #+#    #+#             */
/*   Updated: 2021/06/09 17:46:50 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_export_var(void *content)
{
	t_var	*var;

	var = content;
	if (var->flags & EXPORT_VAR)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(var->name, 1);
		if (var->value)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(var->value, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
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

int	builtin_export(t_shell *sh, int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc > 1)
	{
		while (--argc)
		{
			if (!is_valid_var(argv[i]))
				print_identifier_error(sh, argv[0], argv[i], 1);
			else
				build_var(&argv[i], &sh->env_lst, modify_value);
			i++;
		}
	}
	else
		sh->status = print_export(sh->env_lst);
	return (1);
}
