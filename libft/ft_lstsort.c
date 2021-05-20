/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 17:32:42 by tsierra-          #+#    #+#             */
/*   Updated: 2021/05/20 20:39:43 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstsort(t_list *lst, int (*cmp)())
{
	t_list	*last;
	t_list	*alst;
	void	*ptr;

	ptr = lst;
	last = NULL;
	while (ptr)
	{
		alst = lst;
		ptr = NULL;
		while (alst->next != last)
		{
			if ((cmp(alst->content, alst->next->content) > 0))
			{
				ptr = alst->content;
				alst->content = alst->next->content;
				alst->next->content = ptr;
			}
			alst = alst->next;
		}
		last = alst;
	}
}
