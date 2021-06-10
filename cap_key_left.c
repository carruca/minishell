/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cap_key_left.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccardozo <ccardozo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 13:58:23 by ccardozo          #+#    #+#             */
/*   Updated: 2021/06/10 14:42:25 by ccardozo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cap_key_left(t_cap *cap)
{	
	if (cap->len_cursor)
	{
		tputs(cursor_left, 1, ft_putchar);
		cap->len_cursor--;
	}
	ft_bzero(cap->ch, sizeof(cap->ch));
	cap->check_esc = 0;
	return (0);
}
