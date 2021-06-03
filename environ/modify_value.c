/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 19:22:03 by tsierra-          #+#    #+#             */
/*   Updated: 2021/05/31 19:22:05 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	modify_value(char *value, t_var *var)
{
	char	*str;

	if (!value)
	{
		free(var->value);
		var->value = NULL;
		return (1);
	}
	str = ft_strdup(value);
	free(var->value);
	var->value = str;
	set_flags(var);
	return (1);
}
