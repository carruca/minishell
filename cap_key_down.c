/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cap_key_down.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccardozo <ccardozo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 13:58:17 by ccardozo          #+#    #+#             */
/*   Updated: 2021/06/10 14:42:14 by ccardozo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cap_key_down(t_cap *cap)
{
	if (cap->cli->prev)
	{
		cap->cli = cap->cli->prev;
		find_history(cap);
	}
	ft_bzero(cap->ch, sizeof(cap->ch));
	cap->check_esc = 0;
	return (0);
}
