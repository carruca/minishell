/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 13:28:14 by tsierra-          #+#    #+#             */
/*   Updated: 2021/03/04 13:56:11 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	j;
	char			*a;

	i = 0;
	j = c;
	a = (void *)b;
	while (i < len)
	{
		a[i] = j;
		i++;
	}
	return (b);
}
