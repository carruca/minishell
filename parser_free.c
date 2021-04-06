/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 17:20:32 by tsierra-          #+#    #+#             */
/*   Updated: 2021/04/05 17:50:32 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdlib.h>

void	free_redir(void *redir)
{
	t_redir	*tmp;

	tmp = redir;
	free(tmp->file);
	free(tmp);
}

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
