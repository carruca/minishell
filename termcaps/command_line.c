/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccardozo <ccardozo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 13:59:10 by ccardozo          #+#    #+#             */
/*   Updated: 2021/06/10 15:38:16 by ccardozo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_aux(t_cap *lstcap)
{
	ft_bzero(lstcap->cmd_buff, sizeof(lstcap->cmd_buff));
	lstcap->str = '\0';
	lstcap->index_ch = 0;
	lstcap->check_esc = 0;
	lstcap->cmd_cursor = lstcap->cmd_buff;
	lstcap->len_cursor = 0;
}

void	control_key(t_cap *cap)
{
	if (cap->str == '\e')
		cap->check_esc = TRUE;
	if (!ft_strcmp(cap->ch, tgetstr("ku", 0)))
		cap->index_ch = cap_key_up(cap);
	else if (!ft_strcmp(cap->ch, tgetstr("kd", 0)))
		cap->index_ch = cap_key_down(cap);
	else if (!ft_strcmp(cap->ch, tgetstr("kr", 0)))
	{
		cap->index_ch = 0;
		ft_bzero(cap->ch, sizeof(cap->ch));
	}
	else if (!ft_strcmp(cap->ch, tgetstr("kl", 0)))
	{
		cap->index_ch = 0;
		ft_bzero(cap->ch, sizeof(cap->ch));
	}
	else if (ft_isprint(cap->str) && cap->check_esc == FALSE)
		cap->index_ch = cap_key_printable(cap);
	else if (cap->check_esc == TRUE && cap->ch[2] != '\0')
	{
		cap->index_ch = 0;
		ft_bzero(cap->ch, sizeof(cap->ch));
		cap->check_esc = FALSE;
	}
}

int	cap_nextline_key(t_cap *cap, char **cmd)
{
	t_line	*line;

	line = cap->cli->content;
	if (*cap->cmd_buff || line->origin_line)
	{
		*cmd = next_line_key(cap);
		return (1);
	}
	*cmd = "";
	printf("\n");
	return (0);
}

int	*read_cmdline(char **cmd, t_cap *cap)
{
	init_aux(cap);
	tputs(save_cursor, 1, ft_putchar);
	while (cap->str != NL_KEY)
	{
		read(0, &cap->str, 1);
		if (cap->str == DL_KEY)
			cap_delete_char(cap);
		else if (cap->str == NL_KEY)
		{
			if (cap_nextline_key(cap, &(*cmd)))
				break ;
		}
		else if (cap_control(cap, &*cmd))
			break ;
		else if (cap->str != TAB)
		{
			cap->ch[cap->index_ch++] = cap->str;
			control_key(cap);
		}
	}
	return (0);
}
