/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   increase_shlvl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 19:21:01 by tsierra-          #+#    #+#             */
/*   Updated: 2021/05/31 19:21:03 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	increase_shlvl(char *str, t_var *var)
{
	int	tmp;

	(void)str;
	tmp = ft_atoi(var->value);
	free(var->value);
	var->value = ft_itoa(++tmp);
	return (1);
}
