/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 14:24:02 by tsierra-          #+#    #+#             */
/*   Updated: 2021/05/12 18:25:36 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_buildin_error(t_shell *sh, char *buildin, char *str, int status)
{
	ft_putstr_fd(sh->prompt, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(buildin, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	sh->status = status;
}

int	buildin_cd(t_shell *sh, int	argc, char **argv)
{
	int		ret;
	char	*old_wd;
	char	*new_wc;

	old_wd = getenv("PWD");
	if (argc == 1)
		new_wc = getenv("HOME");
	else
		new_wc = argv[1];
	ret = chdir(new_wc);
	if (!ret)
		printf("%s\n", new_wc);
	else
		print_buildin_error(sh, argv[0], argv[1], 1);
	return (1);
}

int	check_buildin(t_shell *sh, int argc, char **argv)
{
	int ret;

	ret = 0;
	if (argv && !ft_strcmp(argv[0], "cd"))
		ret = buildin_cd(sh, argc, argv);
	return (ret);
}
