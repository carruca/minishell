/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 21:26:23 by tsierra-          #+#    #+#             */
/*   Updated: 2021/06/03 17:51:58 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	executer(t_shell *sh)
{
	t_list	*head;
	t_pip	*apipeline;
//	t_exec	exec;

	head = sh->pipeline_lst;
//	ft_bzero(&exec, sizeof(t_exec));
	while (sh->pipeline_lst)
	{
//		cpy_std_fd(exec.fd.std_fd);
		apipeline = sh->pipeline_lst->content;
		if (apipeline)
			executer_pipeline(apipeline, sh);
//		reset_std_fd(exec.fd.std_fd);
		sh->pipeline_lst = sh->pipeline_lst->next;
	}
	ft_lstclear(&head, free_pipeline);
}
