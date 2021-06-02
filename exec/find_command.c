/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 21:10:31 by tsierra-          #+#    #+#             */
/*   Updated: 2021/05/31 21:11:47 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	find_command(t_shell *sh, t_exec *exec)
{
	if (exec->builtin && !exec->fd.piped)
		execute_builtin(sh, exec);
	else if (!exec->path && exec->argv[0] && *exec->argv[0] && !exec->builtin)
		print_error(sh, exec->argv[0], "command not found", 127);
	else if (exec->path && is_directory(exec->path))
		print_error(sh, exec->argv[0], "is a directory", 126);
	else
		sh->status = executer_command(sh, exec);
}
