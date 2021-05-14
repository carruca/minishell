/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 14:24:02 by tsierra-          #+#    #+#             */
/*   Updated: 2021/05/14 14:10:20 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**environ;

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



int	builtin_cd(t_shell *sh, int	argc, char **argv)
{
	int		ret;
	char	*pwc;
	char	*oldpwd;

	oldpwd = getenv("PWD");
	if (argc == 1)
		pwc = getenv("HOME");
	else
		pwc = argv[1];
	ret = chdir(pwc);
	if (ret < 0)
		print_builtin_error(sh, argv, strerror(errno), 1);
	else
		sh->status = 0;
	return (1);
}

int	check_builtin(t_shell *sh, int argc, char **argv)
{
	int ret;

	ret = 0;
	if (argc && !ft_strcmp(argv[0], "cd"))
		ret = builtin_cd(sh, argc, argv);
	if (argc && !ft_strcmp(argv[0], "exit"))
		ret = builtin_exit(sh, argc, argv);
	return (ret);
}
