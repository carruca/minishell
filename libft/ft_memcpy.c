/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 12:25:12 by tsierra-          #+#    #+#             */
/*   Updated: 2021/03/04 13:55:20 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*a;
	char	*b;

	i = 0;
	a = (void *)dst;
	b = (void *)src;
	if (dst == 0 && src == 0)
		return (0);
	while (i < n)
	{
		a[i] = b[i];
		i++;
	}
	return (a);
}
