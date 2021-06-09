/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_children.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 17:54:18 by tsierra-          #+#    #+#             */
/*   Updated: 2021/06/09 17:55:01 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_children(int *ret, int *sig)
{
	int		status;
	pid_t	pid;

	*sig = 0;
	*ret = 0;
	pid = wait(&status);
	if (pid < 0)
		return (pid);
	if (WIFEXITED(status))
		*ret = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		*sig = WTERMSIG(status);
	if (WIFSTOPPED(status))
		*sig = WSTOPSIG(status);
	if (*ret == -1)
		*ret = errno;
	else if (*sig)
		*ret = *sig + 128;
	return (pid);
}
