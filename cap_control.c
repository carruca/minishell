/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cap_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccardozo <ccardozo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 15:38:28 by ccardozo          #+#    #+#             */
/*   Updated: 2021/06/10 15:57:50 by ccardozo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cap_control_d(t_cap *cap, char **cmd)
{
	if (*cap->cmd_buff)
	{
		cap->index_ch = 0;
		ft_bzero(cap->ch, sizeof(cap->ch));
	}
	else
	{
		printf("\n");
		*cmd = "exit";
		return (1);
	}
	return (0);
}

int	cap_control_c(t_cap *cap, char **cmd)
{
	if (*cap->cmd_buff)
	{
		cap->index_ch = 0;
		ft_bzero(cap->ch, sizeof(cap->ch));
		printf("%s\n", cap->ch);
		*cmd = "";
		while (cap->cli->prev)
			cap->cli = cap->cli->prev;
		return (1);
	}
	else
	{
		printf("%s\n", cap->ch);
		*cmd = "";
		return (1);
	}
	return (0);
}

int	cap_control(t_cap *cap, char **cmd)
{
	if (cap->str == CTRL_D)
	{
		cap_control_d(cap, &(*cmd));
		return (1);
	}
	else if (cap->str == CTRL_C)
	{
		cap_control_c(cap, &(*cmd));
		return (1);
	}
	return (0);
}
