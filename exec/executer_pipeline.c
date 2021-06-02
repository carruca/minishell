/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_pipeline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 21:18:41 by tsierra-          #+#    #+#             */
/*   Updated: 2021/06/02 16:49:47 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_pid(void *content)
{
	t_pid	*pid;

	pid = content;
	printf("pid = %d\n", pid->child);
}

void	executer_pipeline(t_pip *pipeline, t_shell *sh, t_exec *exec)
{
	t_list	*head;

	head = pipeline->cmd_lst;
	while (pipeline->cmd_lst)
	{
		executer_compound(pipeline->cmd_lst, sh, exec);
		pipeline->cmd_lst = pipeline->cmd_lst->next;
	}
//	ft_lstiter(sh->pid_lst, print_pid);
	ft_lstclear(&sh->pid_lst, free);
	ft_lstclear(&head, free_command);
}
