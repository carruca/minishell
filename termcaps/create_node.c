/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccardozo <ccardozo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 14:03:02 by ccardozo          #+#    #+#             */
/*   Updated: 2021/06/10 14:44:25 by ccardozo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_empty_node(t_cap *cap)
{
	t_line	*line;

	line = malloc(sizeof(t_line));
	if (!line)
		error_malloc();
	line->origin_line = ft_strdup("");
	line->clone_line = NULL;
	cap->cli = ft_dlstnew(line);
}

void	insert_node_in_list(t_cap *cap, t_lista *new)
{
	while (cap->cli->prev)
		cap->cli = cap->cli->prev;
	new->prev = cap->cli;
	if (cap->cli->next)
	{
		new->next = cap->cli->next;
		cap->cli->next->prev = new;
	}
	cap->cli->next = new;
}

void	create_node(t_cap *cap)
{
	t_lista	*new;
	t_line	*line;
	t_line	*content;

	content = cap->cli->content;
	line = malloc(sizeof(t_line));
	if (!line)
		error_malloc();
	if (!content->clone_line)
	{
		line->origin_line = ft_strdup(cap->cmd_buff);
		line->clone_line = NULL;
	}
	else
	{
		line->origin_line = ft_strdup(cap->cmd_buff);
		line->clone_line = NULL;
		free(content->clone_line);
		content->clone_line = NULL;
	}
	new = ft_dlstnew(line);
	insert_node_in_list(cap, new);
}
