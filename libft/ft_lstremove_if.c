/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremove_if.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 16:50:54 by tsierra-          #+#    #+#             */
/*   Updated: 2021/05/24 16:51:46 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstremove_if(t_list **alst, void *content, int (*cmp)(), void (*del)(void *))
{
	t_list	*current;
	t_list	*prev;

	current = *alst;
	prev = NULL;
	while (current)
	{
		if (!cmp(content, current->content))
		{
			if (prev)
				prev->next = current->next;
			else
			{
				*alst = (*alst)->next;
				prev = *alst;
			}
			ft_lstdelone(current, del);
			current = prev;
		}
		prev = current;
		if (current)
			current = current->next;
	}
}
