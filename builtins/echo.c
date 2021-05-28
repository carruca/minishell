/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 19:49:41 by tsierra-          #+#    #+#             */
/*   Updated: 2021/05/28 19:50:30 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_flag(char *arg, int flag)
{
	int	pos;

	pos = 0;
	if (arg[pos] == '-' && arg[pos + 1])
	{
		pos++;
		while (arg[pos] == flag)
			pos++;
		if (arg[pos] == '\0')
			return (1);
	}
	return (0);
}

int	builtin_echo(t_shell *sh, char **argv)
{
	int	new_line;

	new_line = 1;
	while (*argv && is_flag(*argv, 'n'))
	{
		new_line = 0;
		argv++;
	}
	if (*argv)
		ft_putstr_fd(*argv, 1);
	while (*argv && *(++argv))
	{
		ft_putstr_fd(" ", 1);
		ft_putstr_fd(*argv, 1);
	}
	if (new_line)
		ft_putstr_fd("\n", 1);
	sh->status = 0;
	return (1);
}
