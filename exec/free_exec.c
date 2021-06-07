/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 21:08:06 by tsierra-          #+#    #+#             */
/*   Updated: 2021/06/07 21:11:33 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_exec(t_exec *exec)
{
	if (exec->argc)
		ft_free_tab(exec->argv);
	if (exec->env)
		ft_free_tab(exec->env);
	if (exec->path)
		free(exec->path);
}
