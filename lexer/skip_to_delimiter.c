/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_to_delimiter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 19:30:58 by tsierra-          #+#    #+#             */
/*   Updated: 2021/06/09 19:31:18 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_to_delimiter(char *str, char *set, int *len)
{
	int		i;
	int		quoted;

	i = 0;
	*len = 0;
	quoted = 0;
	while (str[i] != '\0')
	{
		is_quoted(str[i], &quoted);
		if (ft_strchr(set, str[i]) && !quoted)
		{
			i += (*len == 0);
			*len += (*len == 0 && str[i - 1] != ' ' && str[i - 1] != '\t');
			*len += (str[i - 1] == str[i] && !ft_strchr(" \t|<;", str[i]));
			i += (str[i - 1] == str[i] && !ft_strchr(" \t|<;", str[i]));
			break ;
		}
		i++;
		(*len)++;
	}
	return (i);
}
