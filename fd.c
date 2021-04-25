#include "fd.h"

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

void	set_std_fd(int *fd, int *redir_fd, int *std_fd, int *piped, int id)
{
	if (*piped == 0)
		fd[id] = dup(std_fd[id]);
	if (redir_fd[id] > 2)
	{
		dup2(redir_fd[id], fd[id]);
		close(redir_fd[id]);
	}
	set_fd(fd, id);
}

void	set_pipe(int *fd, int *piped)
{
	pipe(fd);
	set_fd(fd, 1);
	*piped = 1;
}
