/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 17:27:50 by tsierra-          #+#    #+#             */
/*   Updated: 2021/05/20 18:13:25 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void *clone_f(void *content)
{
	return (content);
}

t_list	*ft_lstclone(t_list *lst, void (*del)(void *))
{
	return (ft_lstmap(lst, clone_f, del));
}
