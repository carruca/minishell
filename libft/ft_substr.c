/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 11:09:53 by tsierra-          #+#    #+#             */
/*   Updated: 2020/11/12 11:36:02 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	i;

	if (!(new = (char*)malloc(sizeof(char) * (len + 1))) || !s)
		return (NULL);
	i = 0;
	if (start < ft_strlen(s))
	{
		while (i < len && s[start])
		{
			new[i] = s[start];
			i++;
			start++;
		}
	}
	new[i] = '\0';
	return (new);
}
