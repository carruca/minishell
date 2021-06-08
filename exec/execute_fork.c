/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_fork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 21:09:41 by tsierra-          #+#    #+#             */
/*   Updated: 2021/06/08 20:35:03 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_child(t_shell *sh, int fd_in, int *fd_next, t_cmd *cmd)
{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (fd_in)
			dup2(fd_in, 0);
		if (fd_next[0] != 0)
			close(fd_next[0]);
		if (fd_next[1] != 1)
			dup2(fd_next[1], 1);
		if (!set_redir(sh, cmd->redir_lst))
		{
			if (sh->exec.builtin & FORK_BUILTIN)
				execute_builtin(sh, &sh->exec);
			else if (!sh->exec.builtin && !check_error(sh, &sh->exec))
				execve(sh->exec.path, sh->exec.argv, sh->exec.env);
		}
		else
			exit(1);
		close(fd_next[1]);
		exit(0);
}

int	execute_fork(t_shell *sh, int fd_in, int *fd_next, t_cmd *cmd)
{
	sh->lastpid = fork();
	if (sh->lastpid < 0)
		return (1);
	else if (sh->lastpid == 0)
	{
		execute_child(sh, fd_in, fd_next, cmd);
/*		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (fd_in)
			dup2(fd_in, 0);
//		close(fd_next[0]);
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
		exit(0);*/
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
