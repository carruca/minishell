/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 14:24:02 by tsierra-          #+#    #+#             */
/*   Updated: 2021/05/14 15:18:54 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
