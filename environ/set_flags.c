/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 19:23:13 by tsierra-          #+#    #+#             */
/*   Updated: 2021/05/31 19:23:15 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_flags(t_var *var)
{
	if (!ft_strcmp(var->name, "_"))
		set_flag(var, ENV_VAR);
	else if (!var->value)
		set_flag(var, EXPORT_VAR);
	else
		set_flag(var, EXPORT_VAR | ENV_VAR);
}
