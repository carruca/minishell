/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 19:19:03 by tsierra-          #+#    #+#             */
/*   Updated: 2021/05/31 19:19:07 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_identifier_error(t_shell *sh, char *cmd, char *arg, int status)
{
	ft_putstr_fd(sh->prompt, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("´: ", 2);
	ft_putstr_fd("not a valid identifier", 2);
	ft_putstr_fd("\n", 2);
	sh->status = status;
}

void	print_builtin_error(t_shell *sh, char **argv, char *str, int status)
{
	ft_putstr_fd(sh->prompt, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(argv[0], 2);
	ft_putstr_fd(": ", 2);
	if (argv[1] && ft_strcmp(argv[1], "-"))
	{
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	sh->status = status;
}
