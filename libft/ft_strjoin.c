/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 11:57:07 by tsierra-          #+#    #+#             */
/*   Updated: 2020/11/27 12:29:59 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	size_t	i;
	size_t	l;

	if (!s1 || !s2 || !(join = (char*)malloc(sizeof(char)
					* (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		join[i] = s1[i];
		i++;
	}
	join[i] = '\0';
	l = ft_strlen(join);
	i = 0;
	while (s2[i] != '\0')
	{
		join[l + i] = s2[i];
		i++;
	}
	join[l + i] = '\0';
	return (join);
}
