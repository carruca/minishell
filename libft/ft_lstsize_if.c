/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_if.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 12:39:32 by tsierra-          #+#    #+#             */
/*   Updated: 2021/05/07 13:01:49 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize_if(t_list *lst, int (*cmp)())
{
	int	size;

	if (!lst)
		return (0);
	size = 0;
	while (lst)
	{
		if (cmp(lst->content))
			size++;
		lst = lst->next;
	}
	return (size);
}
