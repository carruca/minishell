/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsttoa_if.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 13:25:10 by tsierra-          #+#    #+#             */
/*   Updated: 2021/05/07 13:23:28 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	**ft_lsttoa_if(t_list *lst, int (*cmp)())
{
	char	**new;
	int		counter;
	int		i;

	counter = ft_lstsize_if(lst, cmp);
	new = ft_calloc(counter + 1, sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	while (i < counter)
	{
		if (cmp(lst->content))
		{
			new[i] = ft_strdup((char *)lst->content);
			if (!new[i])
			{
				ft_free_tab(new);
				return (NULL);
			}
			i++;
		}
		lst = lst->next;
	}
	new[i] = NULL;
	return (new);
}
