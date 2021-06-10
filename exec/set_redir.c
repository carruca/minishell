/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 21:09:03 by tsierra-          #+#    #+#             */
/*   Updated: 2021/06/09 17:43:23 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_less(int fd, char *file)
{
	int	fd_redir;

	if (fd)
		close(fd);
	fd_redir = open(file, O_RDONLY);
	return (fd_redir);
}

static int	open_great(int fd, char *file)
{
	int	fd_redir;

	if (fd)
		close(fd);
	fd_redir = open(file, O_CREAT | O_WRONLY | O_TRUNC, 00644);
	return (fd_redir);
}

static int	open_dgreat(int fd, char *file)
{
	int	fd_redir;

	if (fd)
		close(fd);
	fd_redir = open(file, O_CREAT | O_WRONLY | O_APPEND, 00644);
	return (fd_redir);
}

int	set_redir(t_shell *sh, t_list *redir_lst)
{
	t_redir	*redir;
	int		fd[2];

	ft_bzero(fd, sizeof(int) * 2);
	while (redir_lst)
	{
		redir = redir_lst->content;
		if (!redir_file_have_quotes(&redir->file, sh))
			return (1);
		if (redir->type & LESS)
			fd[0] = open_less(fd[0], redir->file);
		else if (redir->type & GREAT)
			fd[1] = open_great(fd[1], redir->file);
		else if (redir->type & DGREAT)
			fd[1] = open_dgreat(fd[1], redir->file);
		if (fd[0] == -1 || fd[1] == -1)
			return (print_error(sh, redir->file, strerror(errno), 1));
		redir_lst = redir_lst->next;
	}
	if (fd[0] > 2)
		set_std_fd(fd[0], 0);
	if (fd[1] > 2)
		set_std_fd(fd[1], 1);
	return (0);
}
