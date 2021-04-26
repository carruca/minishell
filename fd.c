/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 13:23:57 by tsierra-          #+#    #+#             */
/*   Updated: 2021/04/26 14:54:48 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "parser.h"
#include "fd.h"
#include "executer.h"

void	set_fd(int *fd, int id)
{
	dup2(fd[id], id);
	close(fd[id]);
}

void	cpy_std_fd(int *fd)
{
	fd[0] = dup(0);
	fd[1] = dup(1);
}

void	reset_std_fd(int *std_fd)
{
	set_fd(std_fd, 0);
	set_fd(std_fd, 1);
}

void	set_std_fd(t_fd *fd, int id)
{
	if (fd->piped == 0)
		fd->fd[id] = dup(fd->std_fd[id]);
	if (fd->redir_fd[id] > 2)
	{
		dup2(fd->redir_fd[id], fd->fd[id]);
		close(fd->redir_fd[id]);
	}
	set_fd(fd->fd, id);
}

void	set_pipe(int *fd, int *piped)
{
	pipe(fd);
	set_fd(fd, 1);
	*piped = 1;
}
