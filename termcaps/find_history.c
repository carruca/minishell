/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccardozo <ccardozo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 14:03:12 by ccardozo          #+#    #+#             */
/*   Updated: 2021/06/10 14:45:24 by ccardozo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_history(t_cap *cap)
{
	t_line	*line;

	line = cap->cli->content;
	tputs(restore_cursor, 1, ft_putchar);
	tputs(tgetstr("ed", 0), 1, ft_putchar);
	tputs(tgetstr("ce", 0), 1, ft_putchar);
	if (line->clone_line && ft_strcmp(line->clone_line, ""))
	{
		ft_strcpy(cap->cmd_buff, line->clone_line);
		cap->cli_bufflen = ft_strlen(line->clone_line);
		cap->len_cursor = cap->cli_bufflen;
		cap->cmd_cursor = cap->cmd_buff + cap->cli_bufflen;
		ft_putstr_fd(line->clone_line, 1);
	}
	else if (line->origin_line)
	{
		ft_strcpy(cap->cmd_buff, line->origin_line);
		cap->cli_bufflen = ft_strlen(line->origin_line);
		cap->len_cursor = cap->cli_bufflen;
		cap->cmd_cursor = cap->cmd_buff + cap->cli_bufflen;
		ft_putstr_fd(line->origin_line, 1);
	}
}
