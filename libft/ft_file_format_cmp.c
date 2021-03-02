/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_format_cmp.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 12:47:18 by tsierra-          #+#    #+#             */
/*   Updated: 2020/11/27 12:53:17 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_file_format_cmp(char *str, char *format)
{
	char	*format_str;
	int		len_str;
	int		len_format;

	len_str = ft_strlen(str);
	len_format = ft_strlen(format);
	format_str = &str[len_str - len_format];
	if (ft_strncmp(format, format_str, len_format))
		return (0);
	return (1);
}
