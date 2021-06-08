/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_fork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 21:09:41 by tsierra-          #+#    #+#             */
/*   Updated: 2021/06/07 21:14:12 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_fork(t_shell *sh, t_exec *exec, int fd_in, int *fd_next, t_cmd *cmd)
{
	sh->lastpid = fork();
	if (sh->lastpid < 0)
		return (1);
	else if (sh->lastpid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (fd_in)
			dup2(fd_in, 0);
		close(fd_next[0]);
		if (fd_next[1] != 1)
			dup2(fd_next[1], 1);
		if (!set_redir(sh, cmd->redir_lst))
		{
			if (exec->builtin & FORK_BUILTIN)
				execute_builtin(sh, exec);
			else if (!exec->builtin && !check_error(sh, exec))
				execve(exec->path, exec->argv, exec->env);
		}
		close(fd_next[1]);
		exit(0);
	}
	else
	{
		if (fd_in)
			close(fd_in);
		if (fd_next[1] != 1)
			close(fd_next[1]);
	}
	return (0);
}
