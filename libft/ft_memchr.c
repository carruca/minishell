/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 16:57:07 by tsierra-          #+#    #+#             */
/*   Updated: 2021/03/04 13:53:52 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*a;
	unsigned char	d;
	size_t			i;

	i = 0;
	a = (unsigned char *)s;
	d = (unsigned char)c;
	while (n--)
	{
		if (a[i] == d)
			return (a + i);
		i++;
	}
	return (NULL);
}
