/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 13:53:28 by tsierra-          #+#    #+#             */
/*   Updated: 2021/03/08 16:30:49 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtok(char *str, const char *sep)
{
	static char	*ptr;

	if (str)
		ptr = str;
	else if (!ptr)
		return (NULL);
	str = ptr + ft_strspn(ptr, sep);
	ptr = str + ft_strcspn(str, sep);
	if (ptr == str)
	{
		ptr = NULL;
		return (ptr);
	}
	if (*ptr)
		*ptr++ = '\0';
	return (str);
}
