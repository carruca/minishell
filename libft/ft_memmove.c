/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 15:31:37 by tsierra-          #+#    #+#             */
/*   Updated: 2019/11/19 13:33:28 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*a;
	char	*b;

	i = 0;
	a = (void*)dst;
	b = (void*)src;
	if (dst == src)
		return (dst);
	if (src < dst)
	{
		i = len;
		while (i-- > 0)
			a[i] = b[i];
	}
	else
	{
		while (i < len)
		{
			a[i] = b[i];
			i++;
		}
	}
	return (a);
}
