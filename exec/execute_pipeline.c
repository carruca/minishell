/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 17:25:08 by tsierra-          #+#    #+#             */
/*   Updated: 2021/06/07 21:21:09 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_pipeline(t_shell *sh, t_list *cmd_lst)
{
	t_list	*current;
	t_exec	exec;
	int		len_lst;
	int		fd_in;
	int		fd_next[2];

	fd_in = 0;
	len_lst = ft_lstsize(cmd_lst);
	current = cmd_lst;
	while (current)
	{
		ft_bzero(&exec, sizeof(t_exec));
		build_exec(&exec, (t_cmd *)current->content, sh);
		if (len_lst == 1 && exec.builtin)
			execute_builtin(sh, &exec);
		else if (exec.argc > 0)
		{
			if (current->next)
				pipe(fd_next);
			else
				fd_next[1] = 1;
			execute_fork(sh, &exec, fd_in, fd_next, (t_cmd *)current->content);
			fd_in = fd_next[0];
		}
		free_exec(&exec);
		current = current->next;
	}
	while (len_lst--)
		wait(NULL);
	//system("lsof -c minishell");
	return (0);
}
