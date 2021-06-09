/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 17:25:08 by tsierra-          #+#    #+#             */
/*   Updated: 2021/06/09 17:54:50 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_cmd(t_shell *sh, t_list *cmd_lst, int *fd_in)
{
	ft_bzero(&sh->exec, sizeof(t_exec));
	build_exec(&sh->exec, (t_cmd *)cmd_lst->content, sh);
	if (sh->len_lst == 1 && sh->exec.builtin)
	{
		sh->status = set_redir(sh, ((t_cmd *)(cmd_lst->content))->redir_lst);
		if (!sh->status)
			execute_builtin(sh, &sh->exec);
	}
	else
	{
		if (cmd_lst->next)
			pipe(sh->fd_next);
		else
			sh->fd_next[1] = 1;
		execute_fork(sh, *fd_in, sh->fd_next, (t_cmd *)cmd_lst->content);
		*fd_in = sh->fd_next[0];
	}
	free_exec(&sh->exec);
}

int	execute_pipeline(t_shell *sh, t_list *cmd_lst)
{
	t_list	*current;
	int		std_fd[2];
	int		fd_in;
	int		ret;

	fd_in = 0;
	sh->len_lst = ft_lstsize(cmd_lst);
	cpy_std_fd(std_fd);
	current = cmd_lst;
	while (current)
	{
		execute_cmd(sh, current, &fd_in);
		current = current->next;
	}
	reset_std_fd(std_fd);
	if (sh->len_lst > 1)
		set_var("_", NULL, &sh->env_lst, modify_value);
	while (sh->len_lst--)
	{
		if (sh->lastpid == wait_children(&ret, &sh->sig))
			sh->status = ret;
	}
	return (0);
}
