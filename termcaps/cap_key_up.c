/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cap_key_up.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccardozo <ccardozo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 13:58:37 by ccardozo          #+#    #+#             */
/*   Updated: 2021/06/10 14:42:59 by ccardozo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cap_key_up(t_cap *cap)
{
	if (cap->cli->next)
	{
		cap->cli = cap->cli->next;
		find_history(cap);
	}
	ft_bzero(cap->ch, sizeof(cap->ch));
	cap->check_esc = 0;
	return (0);
}
