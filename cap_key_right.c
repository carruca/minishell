/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cap_key_right.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccardozo <ccardozo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 13:58:32 by ccardozo          #+#    #+#             */
/*   Updated: 2021/06/10 14:42:51 by ccardozo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cap_key_right(t_cap *cap)
{
	if (cap->cmd_buff[cap->len_cursor])
	{
		tputs(cursor_right, 1, ft_putchar);
		cap->len_cursor++;
	}
	ft_bzero(cap->ch, sizeof(cap->ch));
	cap->check_esc = 0;
	return (0);
}
