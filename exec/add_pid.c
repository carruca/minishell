/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_pid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 21:35:15 by tsierra-          #+#    #+#             */
/*   Updated: 2021/05/31 21:35:48 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	add_pid(int child_pid, t_list **pid_lst)
{
	int		*pid;
	t_list	*new;

	pid = malloc(sizeof(int));
	if (!pid)
		return (0);
	*pid = child_pid;
	new = ft_lstnew(pid);
	if (!new)
		return (0);
	ft_lstadd_back(pid_lst, new);
	return (1);
}
