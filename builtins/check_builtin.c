/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:58:28 by tsierra-          #+#    #+#             */
/*   Updated: 2021/05/14 15:19:15 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_builtin(t_shell *sh, int argc, char **argv)
{
	int ret;

	ret = 0;
	if (argc > 0)
	{
		if (!ft_strcmp(argv[0], "cd"))
			ret = builtin_cd(sh, argc, argv);
		else if (!ft_strcmp(argv[0], "exit"))
			ret = builtin_exit(sh, argc, argv);
	}
	return (ret);
}

void	print_builtin_error(t_shell *sh, char **argv, char *str, int status)
{
	ft_putstr_fd(sh->prompt, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(argv[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(argv[1], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	sh->status = status;
}
