/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsttoa_if.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 13:25:10 by tsierra-          #+#    #+#             */
/*   Updated: 2021/05/12 17:12:14 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_lsttoa_if(t_list *lst, char *(*cpy)(), int (*cmp)())
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
			new[i] = cpy(lst->content);
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
