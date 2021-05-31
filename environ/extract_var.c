/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 19:20:26 by tsierra-          #+#    #+#             */
/*   Updated: 2021/05/31 19:20:28 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	extract_var(char **str, char **name, char **value)
{
	char	*pos;

	pos = ft_strchr(*str, '=');
	if (!pos)
		*name = *str;
	else
	{
		*pos = '\0';
		*name = *str;
		*value = pos + 1;
	}
}
