/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 11:50:17 by tsierra-          #+#    #+#             */
/*   Updated: 2021/03/01 11:50:19 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*alst;

	alst = *lst;
	if (!alst)
		*lst = new;
	else
	{
		while (alst->next)
			alst = alst->next;
		alst->next = new;
	}
}
