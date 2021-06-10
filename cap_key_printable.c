/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cap_key_printable.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccardozo <ccardozo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 13:58:07 by ccardozo          #+#    #+#             */
/*   Updated: 2021/06/10 14:42:41 by ccardozo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_buff_add(t_cap *cap)
{
	*cap->cmd_cursor = *cap->ch;
	cap->cli_bufflen++;
	cap->len_cursor++;
	cap->cmd_cursor++;
	*cap->cmd_cursor = '\0';
}

int	cap_key_printable(t_cap *cap)
{
	t_line	*line;
	char	*tmp;

	tmp = NULL;
	line = NULL;
	line = cap->cli->content;
	write(1, &cap->str, 1);
	if (cap->cli_bufflen < 2048)
		set_buff_add(cap);
	if (*(line->origin_line) || !cap->cli->prev)
	{
		if (line->clone_line != NULL)
			tmp = line->clone_line;
		line->clone_line = ft_strdup(cap->cmd_buff);
		if (tmp)
			free(tmp);
	}
	ft_bzero(cap->ch, sizeof(cap->ch));
	cap->check_esc = 0;
	return (0);
}
