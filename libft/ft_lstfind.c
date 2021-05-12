/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 13:17:58 by tsierra-          #+#    #+#             */
/*   Updated: 2021/03/08 13:19:54 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstfind(t_list *lst, void *content, int (*cmp)(void *, void *))
{
	if (lst && cmp)
	{
		while (lst)
		{
			if (!cmp(content, lst->content))
				return (lst);
			lst = lst->next;
		}
	}
	return (NULL);
}
