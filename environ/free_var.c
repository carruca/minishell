/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 19:20:34 by tsierra-          #+#    #+#             */
/*   Updated: 2021/05/31 19:20:36 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_var(void *var)
{
	t_var	*tmp;

	tmp = var;
	free(tmp->name);
	if (tmp->value)
		free(tmp->value);
	free(tmp);
	tmp = NULL;
}
