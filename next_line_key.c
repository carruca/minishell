/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_line_key.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccardozo <ccardozo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 14:17:58 by ccardozo          #+#    #+#             */
/*   Updated: 2021/06/10 14:46:37 by ccardozo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*next_line_key(t_cap *cap)
{
	t_line	*line;

	line = NULL;
	write(1, "\n", 1);
	if (*cap->cmd_buff)
	{
		create_node(cap);
		cap->cli_bufflen = 0;
		while (cap->cli->prev)
			cap->cli = cap->cli->prev;
		if (cap->cli->next->content)
		{
			line = cap->cli->next->content;
			free(line->clone_line);
			return (line->origin_line);
		}
	}	
	else
	{
		while (cap->cli->prev)
			cap->cli = cap->cli->prev;
		return ("");
	}
	return (NULL);
}
