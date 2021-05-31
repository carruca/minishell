/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_name_cmp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 19:20:05 by tsierra-          #+#    #+#             */
/*   Updated: 2021/05/31 19:20:06 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env_name_cmp(void *name, void *var)
{
	char	*name_tmp;
	t_var	*var_tmp;

	name_tmp = name;
	var_tmp = var;
	return (ft_strcmp(name_tmp, var_tmp->name) != 0);
}
