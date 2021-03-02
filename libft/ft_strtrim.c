/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 14:12:45 by tsierra-          #+#    #+#             */
/*   Updated: 2019/11/27 14:07:59 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	size_t	start;
	char	*copys1;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]) != NULL)
		start++;
	len = ft_strlen(&s1[start]);
	if (len != 0)
	{
		while (s1[start + len - 1]
				&& ft_strchr(set, s1[start + len - 1]) != NULL)
			len--;
	}
	if ((copys1 = (char*)malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	copys1 = ft_strncpy(copys1, &s1[start], len);
	copys1[len] = '\0';
	return (copys1);
}
