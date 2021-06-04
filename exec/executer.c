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
	t_pip	*pipeline;

	head = sh->pipeline_lst;
	while (sh->pipeline_lst)
	{
		pipeline = sh->pipeline_lst->content;
		if (pipeline)
			execute_pipeline(sh, pipeline->cmd_lst);
			//executer_pipeline(pipeline, sh);
		sh->pipeline_lst = sh->pipeline_lst->next;
	}
	ft_lstclear(&head, free_pipeline);
}
