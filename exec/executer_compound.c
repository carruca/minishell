/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_compound.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 21:17:03 by tsierra-          #+#    #+#             */
/*   Updated: 2021/05/31 21:24:27 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	executer_compound(t_list *cmd_lst, t_shell *sh, t_exec *exec)
{
	t_cmd	*cmd;

	cmd = cmd_lst->content;
	//build_command
	//is builtin and !cmd_lst->next
	//pipe and redir
	//error command
	//execute_command
	sh->status = set_redir_fd(cmd->redir_lst, exec->fd.redir_fd, sh);
	set_std_fd(&exec->fd, 0);
	exec->fd.piped = 0;
	if (cmd_lst->next)
		set_pipe(exec->fd.fd, &exec->fd.piped);
	set_std_fd(&exec->fd, 1);
	if (cmd->args_lst && exec->fd.redir_fd[0] != -1 && exec->fd.redir_fd[1] != -1)
		build_command(cmd, sh, exec);
}
