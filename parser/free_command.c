/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 18:57:57 by tsierra-          #+#    #+#             */
/*   Updated: 2021/06/09 18:58:21 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_command(void *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	if (tmp->args_lst)
	{
		if (tmp->args_lst->content)
			ft_lstclear(&tmp->args_lst, free);
		else
			free(tmp->args_lst);
	}
	if (tmp->redir_lst)
	{
		if (tmp->redir_lst->content)
			ft_lstclear(&tmp->redir_lst, free_redir);
		else
			free(tmp->redir_lst);
	}
	free(tmp);
}
