/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 19:19:39 by tsierra-          #+#    #+#             */
/*   Updated: 2021/05/31 19:19:40 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	add_var(t_var *var, t_list **env_lst)
{
	t_list	*new_lst;

	new_lst = ft_lstnew(var);
	if (!new_lst)
		return (0);
	ft_lstadd_back(env_lst, new_lst);
	return (1);
}
