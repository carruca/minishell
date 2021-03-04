/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_tab_remove.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 13:43:30 by tsierra-          #+#    #+#             */
/*   Updated: 2021/03/04 16:55:25 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strlen_no_tab(char *str)
{
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '\t')
			len++;
		i++;
	}
	return (len);
}

char	*ft_str_tab_remove(char *str)
{
	size_t	len;
	int		i;
	char	*copy;

	len = ft_strlen_no_tab(str);
	copy = malloc(sizeof(char) * (len + 1));
	if (!copy)
		return (NULL);
	i = 0;
	len = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '\t')
		{
			copy[len] = str[i];
			len++;
		}
		i++;
	}
	copy[len] = '\0';
	return (copy);
}
