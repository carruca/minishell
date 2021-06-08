/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 21:48:38 by tsierra-          #+#    #+#             */
/*   Updated: 2021/06/08 22:35:12 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_std_fd(int fd, int std)
{
	dup2(fd, std);
	close(fd);
}

void	cpy_std_fd(int *fd)
{
	fd[0] = dup(0);
	fd[1] = dup(1);
}

void	reset_std_fd(int *fd)
{
	set_std_fd(fd[0], 0);
	set_std_fd(fd[1], 1);
}
