/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redir_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 21:15:02 by tsierra-          #+#    #+#             */
/*   Updated: 2021/06/02 19:57:32 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_redir_fd(t_list *redir_lst, int *fd, t_shell *sh)
{
	t_redir		*aredir;

//	ft_bzero(fd, sizeof(fd));
	while (redir_lst)
	{
		aredir = redir_lst->content;
		if (!redir_file_have_quotes(&aredir->file, sh))
		{
			fd[0] = -1;
			return (1);
		}
		if (aredir->type == LESS)
			fd[0] = open(aredir->file, O_RDONLY);
		else if (aredir->type == GREAT)
			fd[1] = open(aredir->file, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
		else if (aredir->type == DGREAT)
			fd[1] = open(aredir->file, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
		if (fd[0] == -1 || fd[1] == -1)
		{
			print_error(sh, aredir->file, strerror(errno), 1);
			return (1);
		}
		redir_lst = redir_lst->next;
	}
	return (0);
}
