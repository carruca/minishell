/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 18:58:44 by tsierra-          #+#    #+#             */
/*   Updated: 2021/06/09 18:59:13 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_pipeline(void *pipeline)
{
	t_pip	*tmp;

	tmp = pipeline;
	if (tmp->cmd_lst)
	{
		if (tmp->cmd_lst->content)
			ft_lstclear(&tmp->cmd_lst, free_command);
		else
			free(tmp->cmd_lst);
	}
	free(tmp);
}
