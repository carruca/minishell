/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_pipeline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 21:18:41 by tsierra-          #+#    #+#             */
/*   Updated: 2021/06/03 18:26:32 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_pid(void *content)
{
	t_pid	*pid;

	pid = content;
	printf("pid = %d\n", pid->child);
}

void	executer_pipeline(t_pip *pipeline, t_shell *sh)
{
	t_list	*head;
	t_list	*lst;
	int		child_counter;
	t_exec	exec;

	head = pipeline->cmd_lst;
	ft_bzero(&exec, sizeof(t_exec));
	cpy_std_fd(exec.fd.std_fd);
	while (pipeline->cmd_lst)
	{
		executer_compound(pipeline->cmd_lst, sh, &exec);
		pipeline->cmd_lst = pipeline->cmd_lst->next;
	}
	reset_std_fd(exec.fd.std_fd);
	child_counter = ft_lstsize(sh->pid_lst);
	if (child_counter > 0)
	{
		lst = sh->pid_lst;
		while (lst)
		{
			wait(NULL);
			lst = lst->next;
		}
	}
//	system("lsof -c minishell");
	ft_lstclear(&sh->pid_lst, free);
	ft_lstclear(&head, free_command);
}
