/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 21:08:32 by tsierra-          #+#    #+#             */
/*   Updated: 2021/06/07 21:12:26 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_error(t_shell *sh, t_exec *exec)
{
	if (!exec->path && exec->argv[0] && *exec->argv[0] && !exec->builtin)
		return (print_error(sh, exec->argv[0], "command not found", 127));
	else if (exec->path && is_directory(exec->path))
		return (print_error(sh, exec->argv[0], "is a directory", 126));
	return (0);
}
