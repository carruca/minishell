/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:08:34 by tsierra-          #+#    #+#             */
/*   Updated: 2021/05/14 16:05:41 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_exit(t_shell *sh, int argc, char **argv)
{
	int	status;

	status = 0;
	ft_putstr_fd(argv[0], 1);
	ft_putstr_fd("\n", 1);
	if (argc > 1)
	{
		status = ft_atoi(argv[1]);
		if (status == -1)
		{
			print_builtin_error(sh, argv, "numeric argument required", 1);
			status = 2;
		}
		else if (argc > 2)
		{
			print_builtin_error(sh, argv, "too many arguments", 1);
			status = 1;
		}
	}
	system("leaks minishell");
	exit(status);
}
