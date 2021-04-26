/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 13:24:05 by tsierra-          #+#    #+#             */
/*   Updated: 2021/04/26 15:08:20 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FD_H
# define FD_H

typedef struct s_fd
{
	int	fd[2];
	int	std_fd[2];
	int	redir_fd[2];
	int	piped;
}		t_fd;

void	set_fd(int *fd, int id);
void	cpy_std_fd(int *fd);
void	reset_std_fd(int *fd);
void	set_std_fd(t_fd *fd, int id);
void	set_pipe(int *fd, int *piped);

#endif
